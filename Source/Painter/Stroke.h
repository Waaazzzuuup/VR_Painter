#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Save/PainterSaveGame.h"

#include "Stroke.generated.h"

UCLASS()
class PAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	AStroke();
	
	void UpdateStroke(FVector CursorLocation);
	void SetThickness(float NewThickness);
	void SetMaterialColor(FVector NewColor);

	FStrokeState SerializeToStruct() const;
	// receive address here as struct can be quite large
	static AStroke* SpawnAndDeserializeFromStruct(UWorld* World, const FStrokeState& StrokeState);

private:

	FTransform GetNextSegmentTransform(FVector CursorLocation) const;
	FTransform GetNextJointTransform(FVector CursorLocation) const;

	FVector GetNextSegmentScale(FVector CursorLocation) const;
	FVector GetNextSegmentLocation(FVector CursorLocation) const;
	FQuat GetNextSegmentRotation(FVector CursorLocation) const;

	void SetupStrokeParameters();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	FVector PreviousCursorLocation;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* StrokeMeshes;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* JointMeshes;

	UPROPERTY()
	TArray<FVector> StrokePoints;
	
	UPROPERTY()
	float Thickness;

	UPROPERTY()
	FVector MaterialColor;

	bool IsThicknessSet;
	bool IsMaterialColorSet;
};
