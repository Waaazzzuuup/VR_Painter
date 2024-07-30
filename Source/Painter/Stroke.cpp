#include "Stroke.h"


// Sets default values
AStroke::AStroke()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("StrokeMeshes"));
	StrokeMeshes->SetupAttachment(Root);
}


void AStroke::UpdateStroke(FVector CursorLocation)
{
	FTransform StrokeTransform;
	StrokeTransform.SetLocation(CursorLocation);
	StrokeMeshes->AddInstance(StrokeTransform);
	PreviousCursorLocation = CursorLocation;
}
