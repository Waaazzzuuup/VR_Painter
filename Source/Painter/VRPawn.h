#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "HandControllerBase.h"

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
	TSubclassOf<AHandControllerBase> RightHandControllerClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftHandControllerClass;

	UPROPERTY()
	AHandControllerBase* RightHandController;

	UPROPERTY()
	AHandControllerBase* LeftHandController;

	UPROPERTY()
	AController* PC;

	void RightTriggerPressed();
	void RightTriggerReleased();
	void DeleteLastStrokeButtonPressed();
	void PaginateRightAxisInput(float AxisValue);
	void UpdateCurrentPage(int32 Offset);
	
	int32 LastPageOffset = 0;

	UPROPERTY(EditDefaultsOnly)
	float RightAxisThreshold = 0.8f;
};
