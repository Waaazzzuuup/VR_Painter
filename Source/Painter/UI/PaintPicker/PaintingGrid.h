#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"

#include "PaintingGrid.generated.h"

UCLASS()
class PAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPainting();

protected:
	// last "magic" is to bind something samename-sametype to this property
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UUniformGridPanel* PaintingsGrid;
};
