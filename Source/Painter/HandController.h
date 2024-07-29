#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "Stroke.h"
#include "GameFramework/Actor.h"
#include "HandController.generated.h"

UCLASS()
class PAINTER_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	AHandController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void TriggerPressed();
	void TriggerReleased();

private:
	UPROPERTY()
	UMotionControllerComponent* MotionController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AStroke> StrokeClass;

	UPROPERTY(EditAnywhere)
	AStroke* StrokeObj;
	
};
