#include "PaintBrushHandController.h"


APaintBrushHandController::APaintBrushHandController()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentStroke = nullptr;
	BrushTip = CreateDefaultSubobject<USceneComponent>(TEXT("BrushTip"));
	BrushTip->SetupAttachment(GetRootComponent());
}


void APaintBrushHandController::BeginPlay()
{
	Super::BeginPlay();
	BrushTipLocation = BrushTip->GetComponentLocation();
}


void APaintBrushHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentStroke)
	{
		//CurrentStroke->UpdateStroke(GetActorLocation());
		CurrentStroke->UpdateStroke(GetTransform().TransformPosition(BrushTipLocation));
	}
}


void APaintBrushHandController::TriggerPressed()
{
	if (StrokeClass == nullptr) return;

	//CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass, GetActorLocation(), FRotator());
	CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass, GetTransform().TransformPosition(BrushTipLocation), FRotator());
}


void APaintBrushHandController::TriggerReleased()
{
	CurrentStroke = nullptr;
}