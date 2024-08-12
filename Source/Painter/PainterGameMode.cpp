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

	UPainterSaveGame* SaveGame = UPainterSaveGame::Load(SlotName);
	if (SaveGame == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO GAME: %s"), *SlotName);
		return;
	}
	
	SaveGame->DeserializeToWorld(GetWorld());
	UStereoLayerFunctionLibrary::HideSplashScreen();
	UE_LOG(LogTemp, Warning, TEXT("Loaded game: %s"), *SlotName);
}
