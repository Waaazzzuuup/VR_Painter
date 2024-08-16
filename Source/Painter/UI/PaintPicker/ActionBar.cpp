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
	if (ParentPicker) ParentPicker->AddPainting();
}


void UActionBar::ButtonDeleteClicked()
{
	if (ParentPicker) ParentPicker->ToggleDeleteMode();
}
