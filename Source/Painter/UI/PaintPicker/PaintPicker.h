#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"

#include "PaintPicker.generated.h"

UCLASS()
class PAINTER_API APaintPicker : public AActor
{
	GENERATED_BODY()
	
public:	
	APaintPicker();

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PaintGrid;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ActionBar;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

};
