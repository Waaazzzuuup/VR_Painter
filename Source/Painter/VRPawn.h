#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "HandController.h"
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
	TSubclassOf<AHandController> HandControllerClass;

	UPROPERTY()
	AHandController* RightHandController;

	UPROPERTY()
	AController* PC;

	void RightTriggerPressed();
	void RightTriggerReleased();
};
