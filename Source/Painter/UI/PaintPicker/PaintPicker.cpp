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
	
	RefreshSlots();
}


void APaintPicker::RefreshSlots()
{
	PaintingsGrid = Cast<UPaintingGrid>(PaintGrid->GetUserWidgetObject());
	if (PaintingsGrid == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("Pages: %d"), GetNumberOfPages());

	PaintingsGrid->AddPageDot(true);
	PaintingsGrid->AddPageDot(false);
	PaintingsGrid->AddPageDot(false);
	
	PaintingsGrid->ClearAllPaintings();
	int32 index = 0;
	for (FString SlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
	{
		PaintingsGrid->AddPainting(index, SlotName);
		index++;
	}
}


void APaintPicker::AddPainting()
{
	UPainterSaveGame::Create();
	RefreshSlots();
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
