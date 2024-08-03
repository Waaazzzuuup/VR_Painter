#include "HandControllerBase.h"

AHandControllerBase::AHandControllerBase()
{
	PrimaryActorTick.bCanEverTick = false;
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);
	MotionController->SetTrackingSource(EControllerHand::Right);
	MotionController->SetShowDeviceModel(true);

}
