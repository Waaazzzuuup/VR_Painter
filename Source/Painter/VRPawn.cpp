#include "VRPawn.h"
#include "Engine/World.h"


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
	
	UPainterSaveGame* SaveGameObj = UPainterSaveGame::Create();
	if (SaveGameObj == nullptr) return;

	SaveGameObj->SetState("SavedOnBeginPlay");
	if(SaveGameObj->Save())
	{
		CurrentSlotName = SaveGameObj->GetSlotName();	
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
	UPainterSaveGame* SaveGameObj = UPainterSaveGame::Load(CurrentSlotName);
	if (SaveGameObj)
	{
		SaveGameObj->SetState("SavedByButton");
		SaveGameObj->SerializeFromWorld(GetWorld());
		SaveGameObj->Save();
	}
}

void AVRPawn::Load()
{
	UPainterSaveGame* SaveGameObj = UPainterSaveGame::Load(CurrentSlotName);
	if (SaveGameObj == nullptr) return;
	SaveGameObj->DeserializeToWorld(GetWorld());
}


