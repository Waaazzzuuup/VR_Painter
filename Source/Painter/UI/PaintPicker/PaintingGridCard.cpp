#include "Painter/UI/PaintPicker/PaintingGridCard.h"


void UPaintingGridCard::SetPaintingName(FString PaintingName)
{
	SlotName->SetText(FText::FromString(PaintingName));
}
