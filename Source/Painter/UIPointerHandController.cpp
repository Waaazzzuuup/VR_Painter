#include "UIPointerHandController.h"

AUIPointerHandController::AUIPointerHandController()
{
	WidgetInteractionComp = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	WidgetInteractionComp->SetupAttachment(GetRootComponent());
	// let it be there for now
	SetTrackingHand(EControllerHand::Right);
}

void AUIPointerHandController::TriggerPressed()
{
	Super::TriggerPressed();
	WidgetInteractionComp->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandController::TriggerReleased()
{
	Super::TriggerReleased();
	WidgetInteractionComp->ReleasePointerKey(EKeys::LeftMouseButton);
}
