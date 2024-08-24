#include "Painter/UI/PaintPicker/PaintingGrid.h"

#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"


void UPaintingGrid::AddPainting(int32 PaintingIndex, FString PaintingName)
{
	if (PaintingsGrid == nullptr) return;
	
	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
	if (NewWidget == nullptr) return;

	NewWidget->SetPaintingName(PaintingName);
	NewWidget->SetParentPicker(ParentPicker);
	
	USizeBox* Cell = Cast<USizeBox>(PaintingsGrid->GetChildAt(PaintingIndex));
	if (Cell == nullptr) return;
	
	Cell->AddChild(NewWidget);
}


void UPaintingGrid::ClearAllPaintings()
{
	if(PaintingsGrid == nullptr) return;
	for (int32 i = 0; i < PaintingsGrid->GetChildrenCount(); i++)
	{
		USizeBox* Cell = Cast<USizeBox>(PaintingsGrid->GetChildAt(i));
		if (Cell == nullptr) continue;
		Cell->ClearChildren();
	}
}


void UPaintingGrid::ClearAllPageDots()
{
	if(PagesDots == nullptr) return;
	PagesDots->ClearChildren();
}

// bool is for "graying" out the dots
void UPaintingGrid::AddPageDot(bool Active)
{
	if (PagesDots == nullptr) return;  

	UPageDot* NewPageDot = CreateWidget<UPageDot>(GetWorld(), PageDotClass);
	if (NewPageDot == nullptr) return;

	NewPageDot->SetActive(Active);

	UHorizontalBoxSlot* BoxSlot = PagesDots->AddChildToHorizontalBox(NewPageDot);
	BoxSlot->SetPadding(FMargin(8.0, 0.0, 0.0, 0.0));
}


int32 UPaintingGrid::GetNumberOfSlots() const
{
	if (PaintingsGrid== nullptr) return 0;
	return PaintingsGrid->GetChildrenCount();
}
