#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "HandControllerBase.h"
#include "Save/PainterSaveGame.h"

#include "VRPawn.generated.h"


UCLASS()
class PAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	AVRPawn();

protected:
	virtual void BeginPlay() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* VRRoot;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> PaintBrushHandControllerClass;

	UPROPERTY()
	AHandControllerBase* RightPaintBrushHandController;

	UPROPERTY()
	AController* PC;

	void RightTriggerPressed();
	void RightTriggerReleased();

	void Save();
};
