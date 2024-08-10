#include "Painter/UI/PaintPicker/PaintingGridCard.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"


void UPaintingGridCard::SetPaintingName(FString NewPaintingName)
{
	PaintingName = NewPaintingName;
	SlotName->SetText(FText::FromString(PaintingName));
	CardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{
	// fix for long vr level loading 
	UStereoLayerFunctionLibrary::ShowSplashScreen();
	UGameplayStatics::OpenLevel(GetWorld(), "Canvas", true, "SlotName="+PaintingName);
}
