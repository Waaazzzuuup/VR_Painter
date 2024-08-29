#include "PainterGameMode.h"

#include "Stroke.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"
#include "Save/PainterSaveGame.h"


void APainterGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");
}


void APainterGameMode::BeginPlay()
{
	Super::BeginPlay();
	Load();
	UStereoLayerFunctionLibrary::HideSplashScreen();
}


void APainterGameMode::Save() const
{
	UPainterSaveGame* SaveGame = UPainterSaveGame::Load(SlotName);
	if (SaveGame == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CANT SAVE GAME: %s"), *SlotName);
		return;
	}
	SaveGame->SerializeFromWorld(GetWorld());
	SaveGame->Save();
}


void APainterGameMode::Load() const
{
	UPainterSaveGame* SaveGame = UPainterSaveGame::Load(SlotName);
	if (SaveGame == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO GAME: %s"), *SlotName);
		return;
	}
	
	SaveGame->DeserializeToWorld(GetWorld());
}


void APainterGameMode::SaveAndQuit()
{
	Save();
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}


void APainterGameMode::DeleteLastStroke()
{
	// we dont need to iterate over every actor, but we need to get them all (its slow)
	// actually we dont need to cast it to Stroke, as we simply destroy it
	TArray<AActor*> StrokesInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStroke::StaticClass(), StrokesInWorld);
	const int32 n = StrokesInWorld.Num();
	if (n > 1)
	{
		StrokesInWorld[n - 1] -> Destroy();
	}
}

void APainterGameMode::ChangeThickness()
{
	ThicknessIndex++;
	if (ThicknessIndex > sizeof(Thicks)/sizeof(Thicks[0]) - 1 ) ThicknessIndex = 0;
	CurrentThickness = Thicks[ThicknessIndex];
}
