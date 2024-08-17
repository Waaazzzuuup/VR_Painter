#include "Painter/UI/PaintPicker/PaintingGrid.h"

#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting(int32 PaintingIndex, FString PaintingName)
{
	if (PaintingsGrid == nullptr) return;
	
	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
	if (NewWidget == nullptr) return;

	NewWidget->SetPaintingName(PaintingName);
	
	USizeBox* Cell = Cast<USizeBox>(PaintingsGrid->GetChildAt(PaintingIndex));
	if (Cell == nullptr) return;
	
	Cell->AddChild(NewWidget);
	UE_LOG(LogTemp, Warning, TEXT("widget added"));
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
