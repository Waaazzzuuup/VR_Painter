#pragma once

#include "CoreMinimal.h"
#include "PaintPicker.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ActionBar.generated.h"

UCLASS()
class PAINTER_API UActionBar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	void SetParentPicker(APaintPicker* NewParentPicker) {ParentPicker = NewParentPicker;}

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* ButtonDelete;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* ButtonAdd;

private:
	UFUNCTION()
	void ButtonAddClicked();
	
	UFUNCTION()
	void ButtonDeleteClicked();

	UPROPERTY()
	APaintPicker* ParentPicker;
};
