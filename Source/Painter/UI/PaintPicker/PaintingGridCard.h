#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PaintingGridCard.generated.h"


UCLASS()
class PAINTER_API UPaintingGridCard : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPaintingName(FString NewPaintingName);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UTextBlock* SlotName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* CardButton;

private:
	UFUNCTION()
	void CardButtonClicked();

	FString PaintingName;
};
