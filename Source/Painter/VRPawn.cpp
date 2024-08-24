#include "VRPawn.h"

#include "Engine/World.h"
#include "UI/PaintPicker/PaintPicker.h"
#include "EngineUtils.h"
#include "Stroke.h"
#include "Kismet/GameplayStatics.h"


AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(VRRoot);
}


void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	if (RightHandControllerClass)
	{
		RightHandController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
		RightHandController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandController->SetOwner(this);
		RightHandController->SetTrackingHand(EControllerHand::Right);
	}
	
	if (LeftHandControllerClass)
	{
		LeftHandController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
		LeftHandController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		LeftHandController->SetOwner(this);
		LeftHandController->SetTrackingHand(EControllerHand::Left);
	}
}


void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Released, this, &AVRPawn::RightTriggerReleased);
	PlayerInputComponent->BindAxis(TEXT("PaginateRight"), this, &AVRPawn::PaginateRightAxisInput);
}


void AVRPawn::RightTriggerPressed()
{
	if (RightHandController == nullptr) return;
	RightHandController->TriggerPressed();
}


void AVRPawn::RightTriggerReleased()
{
	if (RightHandController == nullptr) return;
	RightHandController->TriggerReleased();
}


void AVRPawn::DeleteLastStrokeButtonPressed()
{
	// we dont need to iterate over every actor, but we need to get them all (its slow)
	// actually we dont need to cast it to Stroke, as we simply destroy it
	TArray<AActor*> StrokesInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStroke::StaticClass(), StrokesInWorld);
	const int32 n = StrokesInWorld.Num();
	UE_LOG(LogTemp, Warning, TEXT("Found %d strokes"), n);
	StrokesInWorld[n - 1] -> Destroy();
}


void AVRPawn::PaginateRightAxisInput(float AxisValue)
{
	int32 PageOffset = 0;
	PageOffset += AxisValue > RightAxisThreshold ? 1 : 0;
	PageOffset += AxisValue < -RightAxisThreshold ? -1 : 0;
	if (PageOffset != LastPageOffset && PageOffset != 0)
	{
		UpdateCurrentPage(PageOffset);
	}
	LastPageOffset = PageOffset;
}


void AVRPawn::UpdateCurrentPage(int32 Offset)
{
	for (TActorIterator<APaintPicker> PaintPickerIter(GetWorld()); PaintPickerIter; ++PaintPickerIter)
	{
		PaintPickerIter->UpdateCurrentPage(Offset);
	}
}


