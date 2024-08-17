#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "HandControllerBase.generated.h"

UCLASS()
class PAINTER_API AHandControllerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AHandControllerBase();
	
	virtual void TriggerPressed() {};
	virtual void TriggerReleased() {};

	void SetTrackingHand(EControllerHand Hand);
	
private:
	UPROPERTY()
	UMotionControllerComponent* MotionController;
};
