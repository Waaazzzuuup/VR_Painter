#include "VRPawn.h"
#include "Engine/World.h"
#include "PaintBrushHandController.h"


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
		RightPaintBrushHandController = GetWorld()->SpawnActor<APaintBrushHandController>(PaintBrushHandControllerClass);
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
	PlayerInputComponent->BindAction(TEXT("LoadAction"), IE_Released, this, &AVRPawn::Load);
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
	UPainterSaveGame* SaveGameObj = UPainterSaveGame::Create();
	SaveGameObj->SetState("puss");
	SaveGameObj->SerializeFromWorld(GetWorld());
	SaveGameObj->Save();
}

void AVRPawn::Load()
{
	UPainterSaveGame* SaveGameObj = UPainterSaveGame::Load();
	if (SaveGameObj == nullptr) return;
	SaveGameObj->DeserializeToWorld(GetWorld());
}


