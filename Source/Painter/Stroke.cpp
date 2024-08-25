#include "Stroke.h"


// Sets default values
AStroke::AStroke()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("StrokeMeshes"));
	StrokeMeshes->SetupAttachment(Root);
	
	JointMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("JointMeshes"));
	JointMeshes->SetupAttachment(Root);
}


void AStroke::UpdateStroke(FVector CursorLocation)
{
	StrokePoints.Add(CursorLocation);
	if (PreviousCursorLocation.IsNearlyZero())
	{
		PreviousCursorLocation = CursorLocation;
		JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));
		return;
	}
	StrokeMeshes->AddInstance(GetNextSegmentTransform(CursorLocation));
	JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));
	PreviousCursorLocation = CursorLocation;
}


FStrokeState AStroke::SerializeToStruct() const
{
	FStrokeState StrokeState;
	StrokeState.StrokeClass = GetClass();
	StrokeState.ControlPoints = StrokePoints;
	return StrokeState;
}


AStroke* AStroke::SpawnAndDeserializeFromStruct(UWorld* World, const FStrokeState& StrokeState)
{
	AStroke* Stroke = World->SpawnActor<AStroke>(StrokeState.StrokeClass);
	for (FVector Location : StrokeState.ControlPoints)
	{
		Stroke->UpdateStroke(Location);
	}
	return Stroke;
}


FTransform AStroke::GetNextSegmentTransform(FVector CursorLocation) const
{
	FTransform SegmentTransform;
	SegmentTransform.SetScale3D(GetNextSegmentScale(CursorLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CursorLocation));
	SegmentTransform.SetLocation(GetNextSegmentLocation(CursorLocation));
	return SegmentTransform;
}


FTransform AStroke::GetNextJointTransform(FVector CursorLocation) const
{
	FTransform JointTransform;
	// location is the same actually
	JointTransform.SetLocation(GetNextSegmentLocation(CursorLocation));
	return JointTransform;
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
	return FQuat::FindBetweenNormals(FVector::ForwardVector, SegmentVectorNormal);
}
