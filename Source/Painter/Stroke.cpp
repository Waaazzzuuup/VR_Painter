#include "Stroke.h"

#include "PainterGameMode.h"


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

	StrokeMaterial = UMaterialInstanceDynamic::Create(BaseStrokeMaterial, this);
}


void AStroke::UpdateStroke(FVector CursorLocation)
{
	StrokePoints.Add(CursorLocation);
	if (PreviousCursorLocation.IsNearlyZero())
	{
		// first point of stroke - get parameters from other places for a setup
		SetupStrokeParameters();	
		
		PreviousCursorLocation = CursorLocation;
		JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));
		return;
	}
	StrokeMeshes->AddInstance(GetNextSegmentTransform(CursorLocation));
	JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));
	PreviousCursorLocation = CursorLocation;
}


void AStroke::SetupStrokeParameters()
{
	// no begin play + cant getworld() in a constructor
	// we get GM here, cos it will be used multiple times
	APainterGameMode* PainterGameMode = Cast<APainterGameMode>(GetWorld()->GetAuthGameMode());

	if (!PainterGameMode) return;
	
	// check if it was set (can be set from deserializing)
	if (!IsThicknessSet)
	{
		SetThickness(PainterGameMode->GetThickness());
	}

	if (!IsMaterialColorSet)
	{
		SetMaterialColor(PainterGameMode->GetStrokeColor());
	}
}


FStrokeState AStroke::SerializeToStruct() const
{
	FStrokeState StrokeState;
	StrokeState.StrokeClass = GetClass();
	StrokeState.ControlPoints = StrokePoints;
	StrokeState.Thickness = Thickness;
	StrokeState.MaterialColor = MaterialColor;
	return StrokeState;
}


AStroke* AStroke::SpawnAndDeserializeFromStruct(UWorld* World, const FStrokeState& StrokeState)
{
	AStroke* Stroke = World->SpawnActor<AStroke>(StrokeState.StrokeClass);
	Stroke->SetThickness(StrokeState.Thickness);
	Stroke->SetMaterialColor(StrokeState.MaterialColor);
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
	JointTransform.SetScale3D(FVector(Thickness, Thickness, Thickness ));
	return JointTransform;
}


FVector AStroke::GetNextSegmentScale(FVector CursorLocation) const
{
	FVector SplineVec = CursorLocation - PreviousCursorLocation;
	return FVector(SplineVec.Size(), Thickness, Thickness);
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
	// splines extrude along the x-axis? whaa
	return FQuat::FindBetweenNormals(FVector::ForwardVector, SegmentVectorNormal);
}


void AStroke::SetThickness(float NewThickness)
{
	Thickness = NewThickness;
	IsThicknessSet = true;
}


void AStroke::SetMaterialColor(FVector NewColor)
{
	MaterialColor = NewColor;
	IsMaterialColorSet = true;
	StrokeMaterial->SetVectorParameterValue("PRM_Color", FLinearColor(MaterialColor));
	JointMeshes->SetMaterial(0, StrokeMaterial);
	StrokeMeshes->SetMaterial(0, StrokeMaterial);
}


