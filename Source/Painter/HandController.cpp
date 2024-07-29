#include "HandController.h"


AHandController::AHandController()
{
	PrimaryActorTick.bCanEverTick = true;
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);
	MotionController->SetTrackingSource(EControllerHand::Right);
	MotionController->SetShowDeviceModel(true);
}


void AHandController::BeginPlay()
{
	Super::BeginPlay();
	
}


void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AHandController::PaintStroke()
{
	if (StrokeObj == nullptr) return;

	StrokeObj = GetWorld()->SpawnActor<AStroke>(StrokeClass, GetActorLocation(), GetActorRotation());
}


