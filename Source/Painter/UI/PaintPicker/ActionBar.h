// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ActionBar.generated.h"

/**
 * 
 */
UCLASS()
class PAINTER_API UActionBar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

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
};
