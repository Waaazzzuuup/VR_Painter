#include "Painter/UI/WidgetTouchComponent.h"

void UWidgetTouchComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool OverSmth = IsOverInteractableWidget();

	// no physical click here - just hover and register it as a click
	if (!bIsClicked && OverSmth)
	{
		bIsClicked = true;
		PressPointerKey(EKeys::LeftMouseButton);
		UE_LOG(LogTemp, Warning, TEXT("Start hovering"));
	}

	if (!OverSmth && bIsClicked)
	{
		bIsClicked = false;
		ReleasePointerKey(EKeys::LeftMouseButton);
		UE_LOG(LogTemp, Warning, TEXT("No longer hovering"));
	}
	
}
