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
	
	void AddPainting();
	void DeletePainting(FString SlotName);
	void ToggleDeleteMode();
	void UpdateCurrentPage(int32 Offset);
	bool IsInDeleteMode() const { return DeleteMode;}

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PaintGrid;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ActionBar;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	void RefreshSlots();
	void RefreshDots();
	void RefreshUI();
	
	// save for later just in case
	UPROPERTY(VisibleAnywhere)
	class UPaintingGrid* PaintingsGrid;
	UPROPERTY(VisibleAnywhere)
	class UActionBar* ActionBarWidget;

	int32 GetNumberOfPages() const;
	
	int32 CurrentPage = 0;

	bool DeleteMode = false;

};
