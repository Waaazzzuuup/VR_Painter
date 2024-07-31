#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"

#include "Stroke.generated.h"

UCLASS()
class PAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	AStroke();
	
	void UpdateStroke(FVector CursorLocation);

private:

	FTransform GetNextSegmentTransform(FVector CursorLocation) const;
	FTransform GetNextJointTransform(FVector CursorLocation) const;

	FVector GetNextSegmentScale(FVector CursorLocation) const;
	FVector GetNextSegmentLocation(FVector CursorLocation) const;
	FQuat GetNextSegmentRotation(FVector CursorLocation) const;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	FVector PreviousCursorLocation;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* StrokeMeshes;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* JointMeshes;
};
