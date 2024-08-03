#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "PainterSaveGame.generated.h"

USTRUCT()
struct FStrokeState
{
	GENERATED_BODY()
	// each stroke can have its own subclass (bp)
	UPROPERTY()
	TSubclassOf<class AStroke> StrokeClass;

	UPROPERTY()
	TArray<FVector> ControlPoints;
};


UCLASS()
class PAINTER_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UPainterSaveGame* Create();
	bool Save();
	static UPainterSaveGame* Load();

	void SetState(FString NewState) {State = NewState;}
	FString GetState() const {return State;}

	void SerializeFromWorld(UWorld* World);
	void DeserializeToWorld(UWorld* World);
	
private:
	UPROPERTY()
	FString State;
	
	UPROPERTY()
	TArray<FStrokeState> Strokes;
};
