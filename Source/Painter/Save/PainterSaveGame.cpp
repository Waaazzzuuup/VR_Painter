#include "PainterSaveGame.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass());
	return Cast<UPainterSaveGame>(NewSaveGame);
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, "test", 0);
}

UPainterSaveGame* UPainterSaveGame::Load()
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot("test", 0));
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	Strokes.Empty();
	// store a subclass for each drawn stroke
	for (TActorIterator<AStroke> StrokeIter(World); StrokeIter; ++StrokeIter)
	{
		Strokes.Add(StrokeIter->GetClass());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld* World)
{
	// clear all strokes in the world
	for (TActorIterator<AStroke> StrokeIter(World); StrokeIter; ++StrokeIter)
	{
		StrokeIter->Destroy();
	}
	// spawn one stroke for each recorded subclass (bp class)
	for (TSubclassOf<AStroke> StrokeClass: Strokes)
	{
		World->SpawnActor<AStroke>(StrokeClass);
	}
}
