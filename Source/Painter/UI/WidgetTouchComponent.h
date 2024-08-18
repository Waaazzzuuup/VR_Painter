#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetInteractionComponent.h"
#include "WidgetTouchComponent.generated.h"


// CUSTOM: widget component override for touch-button purposes. (text here for annotation in BP)
// this magic for component spawn in BP (copied from usual widget interaction component) 
UCLASS(ClassGroup="UserInterface", meta=(BlueprintSpawnableComponent) )
class PAINTER_API UWidgetTouchComponent : public UWidgetInteractionComponent
{
	GENERATED_BODY()

public:
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bIsClicked = false;
};
