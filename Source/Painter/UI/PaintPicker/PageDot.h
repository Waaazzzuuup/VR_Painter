#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "PageDot.generated.h"


UCLASS()
class PAINTER_API UPageDot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetActive(bool Active);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UImage* DotImage;
};
