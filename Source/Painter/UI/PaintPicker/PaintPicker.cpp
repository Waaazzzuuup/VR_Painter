#include "Painter/UI/PaintPicker/PaintPicker.h"

#include "ActionBar.h"
#include "PaintingGrid.h"
#include "Painter/Save/PainterSaveGameIndex.h"


APaintPicker::APaintPicker()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PaintGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintGrid"));
	PaintGrid->SetupAttachment(Root);

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(Root);

}


void APaintPicker::BeginPlay()
{
	Super::BeginPlay();
	
	ActionBarWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBarWidget)
	{
		ActionBarWidget->SetParentPicker(this);
	}

	PaintingsGrid = Cast<UPaintingGrid>(PaintGrid->GetUserWidgetObject());
	
	RefreshUI();
}


void APaintPicker::RefreshSlots()
{
	if (PaintingsGrid == nullptr) return;
	
	PaintingsGrid->ClearAllPaintings();
	
	int32 index = 0;
	for (FString SlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
	{
		PaintingsGrid->AddPainting(index, SlotName);
		index++;
	}
}


void APaintPicker::RefreshDots()
{
	if (PaintingsGrid == nullptr) return;
	PaintingsGrid->ClearAllPageDots();
	for (int32 i = 0; i < GetNumberOfPages(); i++)
	{
		PaintingsGrid->AddPageDot(i == CurrentPage);
	}
}


void APaintPicker::RefreshUI()
{
	RefreshSlots();
	RefreshDots();
}


void APaintPicker::AddPainting()
{
	UPainterSaveGame::Create();
	RefreshUI();
}


void APaintPicker::ToggleDeleteMode()
{
	PaintingsGrid = Cast<UPaintingGrid>(PaintGrid->GetUserWidgetObject());
	if (PaintingsGrid == nullptr) return;
	
	PaintingsGrid->ClearAllPaintings();
}


int32 APaintPicker::GetNumberOfPages() const
{
	if (PaintingsGrid == nullptr) return 0;
	
	int32 TotalNumberOfSlots = UPainterSaveGameIndex::Load()->GetSlotNames().Num();
	int32 SlotsPerPage = PaintingsGrid->GetNumberOfSlots();
	
	return FMath::CeilToInt( (float) TotalNumberOfSlots / SlotsPerPage);
}
