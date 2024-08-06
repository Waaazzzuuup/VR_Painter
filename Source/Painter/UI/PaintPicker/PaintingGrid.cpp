// Fill out your copyright notice in the Description page of Project Settings.


#include "Painter/UI/PaintPicker/PaintingGrid.h"

#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting()
{
	if (PaintingsGrid == nullptr) return;
	
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), GridCardClass);
	if (NewWidget == nullptr) return;
	
	USizeBox* Cell = Cast<USizeBox>(PaintingsGrid->GetChildAt(0));
	if (Cell == nullptr) return;
	
	Cell->AddChild(NewWidget);
}
