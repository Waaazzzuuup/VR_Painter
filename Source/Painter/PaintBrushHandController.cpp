#include "PaintBrushHandController.h"


APaintBrushHandController::APaintBrushHandController()
{
	PrimaryActorTick.bCanEverTick = true;
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);
	MotionController->SetTrackingSource(EControllerHand::Right);
	MotionController->SetShowDeviceModel(true);
}


void APaintBrushHandController::BeginPlay()
{
	Super::BeginPlay();
	
}


void APaintBrushHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentStroke)
	{
		CurrentStroke->UpdateStroke(GetActorLocation());
	}
}


void APaintBrushHandController::TriggerPressed()
{
	if (StrokeClass == nullptr) return;

	CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass, GetActorLocation(), FRotator());
}


void APaintBrushHandController::TriggerReleased()
{
	CurrentStroke = nullptr;
}