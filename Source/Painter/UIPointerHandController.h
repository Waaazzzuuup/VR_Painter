#pragma once

#include "CoreMinimal.h"
#include "HandControllerBase.h"
#include "UIPointerHandController.generated.h"


UCLASS()
class PAINTER_API AUIPointerHandController : public AHandControllerBase
{
	GENERATED_BODY()

	AUIPointerHandController();

public:
	virtual void TriggerPressed() override {};
	virtual void TriggerReleased() override {};
};
