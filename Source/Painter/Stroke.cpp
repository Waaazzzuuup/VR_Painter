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
	if (PreviousCursorLocation.IsNearlyZero())
	{
		PreviousCursorLocation = CursorLocation;
		return;
	}
	StrokeMeshes->AddInstance(GetNextSegmentTransform(CursorLocation));
	PreviousCursorLocation = CursorLocation;
}

FTransform AStroke::GetNextSegmentTransform(FVector CursorLocation) const
{
	FTransform SegmentTransform;
	SegmentTransform.SetScale3D(GetNextSegmentScale(CursorLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CursorLocation));
	SegmentTransform.SetLocation(GetNextSegmentLocation(CursorLocation));
	return SegmentTransform;
}

FVector AStroke::GetNextSegmentScale(FVector CursorLocation) const
{
	FVector SplineVec = CursorLocation - PreviousCursorLocation;
	return FVector(SplineVec.Size(), 1, 1);
}

FVector AStroke::GetNextSegmentLocation(FVector CursorLocation) const
{
	// so world cursor location goes to local in relation to stroke transform
	return GetTransform().InverseTransformPosition(PreviousCursorLocation);
}

FQuat AStroke::GetNextSegmentRotation(FVector CursorLocation) const
{
	FVector SegmentVector = CursorLocation - PreviousCursorLocation;
	FVector SegmentVectorNormal = SegmentVector.GetSafeNormal();
	// splines extrude along the x axis? whaa
	FQuat ResultQuat = FQuat::FindBetweenNormals(FVector::ForwardVector, SegmentVectorNormal);
	UE_LOG(LogTemp, Warning, TEXT("Q %s"), *ResultQuat.ToString());
	return ResultQuat;	
}
