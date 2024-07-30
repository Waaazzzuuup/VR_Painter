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
	// so world cursor location goes to local in relation to stroke transform
	FVector LocalCursorLocation = GetActorTransform().InverseTransformPosition(CursorLocation);
	StrokeTransform.SetLocation(LocalCursorLocation);
	StrokeMeshes->AddInstance(StrokeTransform);
	PreviousCursorLocation = CursorLocation;
}
