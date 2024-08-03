#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "Stroke.h"
#include "GameFramework/Actor.h"
#include "PaintBrushHandController.generated.h"

UCLASS()
class PAINTER_API APaintBrushHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	APaintBrushHandController();

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
	AStroke* CurrentStroke;
	
};
