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

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	FString SlotName;

	UPROPERTY(VisibleAnywhere)
	int32 ThicknessIndex = 0;

	UPROPERTY(EditDefaultsOnly)
	float Thicks[5] = {1, 2, 4, 0.25, 0.5}; 
};
