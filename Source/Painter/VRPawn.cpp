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
	if (PaintBrushHandControllerClass)
	{
		RightPaintBrushHandController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
		RightPaintBrushHandController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightPaintBrushHandController->SetOwner(this);
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
	if (RightPaintBrushHandController == nullptr) return;
	RightPaintBrushHandController->TriggerPressed();
}


void AVRPawn::RightTriggerReleased()
{
	if (RightPaintBrushHandController == nullptr) return;
	RightPaintBrushHandController->TriggerReleased();
}


void AVRPawn::Save()
{
	APainterGameMode* GameMode = Cast<APainterGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr) return;
	GameMode->Save();
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}