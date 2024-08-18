#include "PainterGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"
#include "Save/PainterSaveGame.h"

void APainterGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");
	UE_LOG(LogTemp, Warning, TEXT("NAME: %s"), *SlotName);
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
	UE_LOG(LogTemp, Warning, TEXT("Loaded game: %s"), *SlotName);
}


void APainterGameMode::SaveAndQuit()
{
	Save();
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}
