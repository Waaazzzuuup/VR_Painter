#include "VRPawn.h"
#include "Engine/World.h"
#include "HandController.h"

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
	if (HandControllerClass)
	{
		RightHandController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
		RightHandController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandController->SetOwner(this);
	}

	PC = GetController();
	PC->InputComponent->BindAction(TEXT("RightTrigger"), IE_Pressed, this, &AVRPawn::TriggerPress);
	
}


void AVRPawn::TriggerPress()
{
	RightHandController->PaintStroke();
}


