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


void AHandController::TriggerPressed()
{
	if (StrokeClass == nullptr) return;

	StrokeObj = GetWorld()->SpawnActor<AStroke>(StrokeClass, GetActorLocation(), GetActorRotation());
}


void AHandController::TriggerReleased()
{
	if (StrokeClass == nullptr) return;

	StrokeObj = GetWorld()->SpawnActor<AStroke>(StrokeClass, GetActorLocation(), GetActorRotation());
}