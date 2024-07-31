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
	if (CurrentStroke)
	{
		CurrentStroke->UpdateStroke(GetActorLocation());
	}
}


void AHandController::TriggerPressed()
{
	if (StrokeClass == nullptr) return;

	CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass, GetActorLocation(), FRotator());
}


void AHandController::TriggerReleased()
{
	CurrentStroke = nullptr;
}