#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"

#include "Stroke.generated.h"

UCLASS()
class PAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	AStroke();
	
	void UpdateStroke(FVector CursorLocation);

private:
	USplineMeshComponent* CreateSplineMesh();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMesh* SplineMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* SplineMaterial;

	FVector PreviousCursorLocation;
};
