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

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	FString SlotName;
};
