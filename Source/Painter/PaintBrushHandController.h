#pragma once

#include "CoreMinimal.h"
#include "HandControllerBase.h"
#include "Stroke.h"
#include "GameFramework/Actor.h"
#include "PaintBrushHandController.generated.h"

UCLASS()
class PAINTER_API APaintBrushHandController : public AHandControllerBase
{
	GENERATED_BODY()
	
public:	
	APaintBrushHandController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void TriggerPressed() override;
	virtual void TriggerReleased() override;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AStroke> StrokeClass;

	UPROPERTY(VisibleAnywhere)
	AStroke* CurrentStroke;

	UPROPERTY(EditAnywhere)
	USceneComponent* BrushTip;
	// local to controller tip location, cache it because its const (set in BP)
	UPROPERTY()
	FVector BrushTipLocation;
};
