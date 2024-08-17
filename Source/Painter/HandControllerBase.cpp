#include "HandControllerBase.h"

AHandControllerBase::AHandControllerBase()
{
	PrimaryActorTick.bCanEverTick = false;
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	MotionController->SetShowDeviceModel(true);
	SetRootComponent(MotionController);
}


void AHandControllerBase::SetTrackingHand(EControllerHand Hand)
{
	MotionController->SetTrackingSource(Hand);
}
