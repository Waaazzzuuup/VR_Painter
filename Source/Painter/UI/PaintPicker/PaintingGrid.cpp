// Fill out your copyright notice in the Description page of Project Settings.


#include "Painter/UI/PaintPicker/PaintingGrid.h"

void UPaintingGrid::AddPainting()
{
	if (PaintingsGrid == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("no pointer"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("got some pointer here"));
	}
}
