#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PainterGameMode.generated.h"

UCLASS()
class PAINTER_API APainterGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

public: 
	void Save() const;
	void Load() const;
	
	UFUNCTION(BlueprintCallable)
	void SaveAndQuit();

	UFUNCTION(BlueprintCallable)
	void DeleteLastStroke();

	UFUNCTION(BlueprintCallable)
	void ChangeThickness();

	UFUNCTION(BlueprintCallable)
	void ChangeColor();

	UFUNCTION(BlueprintCallable)
	float GetThickness() const {return CurrentThickness;}

	UFUNCTION(BlueprintCallable)
	FVector GetStrokeColor() const {return CurrentStrokeColor;}

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	FString SlotName;

	UPROPERTY(VisibleAnywhere)
	int32 ThicknessIndex = 0;

	UPROPERTY(VisibleAnywhere)
	float CurrentThickness = 1.0;

	UPROPERTY(EditDefaultsOnly)
	float Thicks[8] = {1, 2, 3, 4, 10, 0.25, 0.5, 0.75};
	
	UPROPERTY(VisibleAnywhere)
	int32 ColorIndex = 0;

	UPROPERTY(VisibleAnywhere)
	FVector Colors[2] = {FVector(0,0,0), FVector(1,0,0)};
	
	UPROPERTY(VisibleAnywhere)
	FVector CurrentStrokeColor = FVector(0,0,0);
};
