#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Painter/HandControllerBase.h"
#include "PaletteMenuHandController.generated.h"


UCLASS()
class PAINTER_API APaletteMenuHandController : public AHandControllerBase
{
	GENERATED_BODY()

public:
	APaletteMenuHandController();

private:
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PaletteMenu;
};
