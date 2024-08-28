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

	UPROPERTY()
	float Thickness;
};


UCLASS()
class PAINTER_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

	
public:
	static UPainterSaveGame* Create();
	bool Save();
	static UPainterSaveGame* Load( FString LoadSlotName );

	void SetState(FString NewState) {State = NewState;}
	FString GetState() const {return State;}

	void SerializeFromWorld(UWorld* World);
	void DeserializeToWorld(UWorld* World);

	FString GetSlotName() const {return SlotName;}

	
private:
	UPROPERTY()
	FString State;

	UPROPERTY()
	FString SlotName;
	
	UPROPERTY()
	TArray<FStrokeState> Strokes;
};