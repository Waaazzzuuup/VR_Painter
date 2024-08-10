#include "PainterGameMode.h"

#include "Kismet/GameplayStatics.h"

void APainterGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");
	UE_LOG(LogTemp, Warning, TEXT("NAME: %s"), *SlotName);
}
