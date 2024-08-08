#include "Painter/UI/PaintPicker/PaintPicker.h"


APaintPicker::APaintPicker()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PaintGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintGrid"));
	PaintGrid->SetupAttachment(Root);

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(Root);

}


void APaintPicker::BeginPlay()
{
	Super::BeginPlay();
	
}


