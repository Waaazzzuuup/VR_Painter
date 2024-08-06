// Fill out your copyright notice in the Description page of Project Settings.


#include "Painter/UI/PaintPicker/PaintingGrid.h"

#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting()
{
	if (PaintingsGrid == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PaintingsGrid is kinda null"));
		return;
	}
	
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), GridCardClass);
	USizeBox* Cell = Cast<USizeBox>(PaintingsGrid->GetChildAt(0));

	if (Cell == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("cell to sizebox casting failed fuck"));
		return;
	}
		
	Cell->AddChild(NewWidget);
	UE_LOG(LogTemp, Warning, TEXT("yes"));
}
