#include "Painter/Save/PainterSaveGameIndex.h"

#include "Kismet/GameplayStatics.h"

const FString UPainterSaveGameIndex::SLOT_NAME = "PainterSlotIndex";

UPainterSaveGameIndex* UPainterSaveGameIndex::Load()
{
	UPainterSaveGameIndex* SlotIndex = Cast<UPainterSaveGameIndex>(UGameplayStatics::LoadGameFromSlot(SLOT_NAME, 0));
	if (!SlotIndex) // new index save needed
	{
		SlotIndex =  Cast<UPainterSaveGameIndex>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
		SlotIndex->Save();
	}
	return SlotIndex;
}


bool UPainterSaveGameIndex::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SLOT_NAME,0);
}


void UPainterSaveGameIndex::AddSaveGame(UPainterSaveGame* SaveGame)
{
	SlotNames.Add(SaveGame->GetSlotName());
}


void UPainterSaveGameIndex::DeleteSaveGame(FString SlotName)
{
	SlotNames.Remove(SlotName);
	bool IsDeleted = UGameplayStatics::DeleteGameInSlot(SlotName, 0);
	if (!IsDeleted)
	{
		UE_LOG(LogTemp, Warning, TEXT("CANT DELETE GAME %s"), *SlotName);
		return;
	}
	Save();
}

