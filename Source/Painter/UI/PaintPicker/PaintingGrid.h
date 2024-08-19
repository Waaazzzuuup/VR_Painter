#pragma once

#include "CoreMinimal.h"
#include "PageDot.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "PaintingGridCard.h"
#include "Components/HorizontalBox.h"

#include "PaintingGrid.generated.h"

UCLASS()
class PAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 PaintingIndex, FString PaintingName);
	void ClearAllPaintings();
	
	void AddPageDot(bool Active);

	int32 GetNumberOfSlots() const;

protected:
	// last "magic" is to bind something samename-sametype to this property
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UUniformGridPanel* PaintingsGrid;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* PagesDots;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaintingGridCard> GridCardClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPageDot> PageDotClass;
};
