#include "PainterSaveGame.h"
#include "EngineUtils.h"
#include "Painter/Stroke.h"
#include "Kismet/GameplayStatics.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	UPainterSaveGame* NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	return NewSaveGame;
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame* UPainterSaveGame::Load(FString LoadSlotName)
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadSlotName, 0));
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	Strokes.Empty();
	// store a struct (class, points) for each drawn stroke
	for (TActorIterator<AStroke> StrokeIter(World); StrokeIter; ++StrokeIter)
	{
		Strokes.Add(StrokeIter->SerializeToStruct());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld* World)
{
	// clear all strokes in the world
	for (TActorIterator<AStroke> StrokeIter(World); StrokeIter; ++StrokeIter)
	{
		StrokeIter->Destroy();
	}
	// spawn one stroke for each recorded struct 
	for (FStrokeState StrokeState: Strokes)
	{
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeState);
	}
}
