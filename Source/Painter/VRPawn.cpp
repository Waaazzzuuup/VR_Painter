#include "VRPawn.h"

#include "PainterGameMode.h"
#include "Engine/World.h"
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
	PlayerInputComponent->BindAction(TEXT("SaveAction"), IE_Released, this, &AVRPawn::Save);
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


void AVRPawn::Save()
{
	APainterGameMode* GameMode = Cast<APainterGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr) return;
	GameMode->Save();
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}