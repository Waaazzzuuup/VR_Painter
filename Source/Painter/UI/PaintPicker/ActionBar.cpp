#include "Painter/UI/PaintPicker/ActionBar.h"

bool UActionBar::Initialize()
{
	const bool IsInitialized = Super::Initialize();
	if (!IsInitialized) return false;

	if (!ButtonAdd) return false;
	ButtonAdd->OnClicked.AddDynamic(this, &UActionBar::ButtonAddClicked);

	if(!ButtonDelete) return false;
	ButtonDelete->OnClicked.AddDynamic(this, &UActionBar::ButtonDeleteClicked);

	return true;
}


void UActionBar::ButtonAddClicked()
{
	//UE_LOG(LogTemp, Warning, TEXT("Add Button Clicked"));
}


void UActionBar::ButtonDeleteClicked()
{
	//UE_LOG(LogTemp, Warning, TEXT("Delete Button Clicked"));
}
