// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "WallSpline.generated.h"

UCLASS()
class ASSIGNMENT3_API AWallSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroySpline();
	void GenerateSpline();
	void CreateWall(FVector& Location);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Root")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	UStaticMesh* SourceMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	UMaterialInterface* SourceMeshMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	TArray<USplineMeshComponent*> SplineComponentsArray;
};
