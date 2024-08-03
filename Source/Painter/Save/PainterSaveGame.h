#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Painter/Stroke.h"

#include "PainterSaveGame.generated.h"



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

	// property for storing ONLY stroke subclasses (like BP children of a stroke)
	UPROPERTY()
	TArray<TSubclassOf<AStroke>> Strokes;
};
