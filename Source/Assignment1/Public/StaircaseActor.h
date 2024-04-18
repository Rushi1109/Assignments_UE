// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaircaseActor.generated.h"

UENUM()
enum class EStaircaseEnum : int8 {
	ClosedStairs UMETA(DisplayName = "Closed Stairs"),
	OpenStairs UMETA(DisplayName = "Open Stairs"),
	BoxStairs UMETA(DisplayName = "Box Stairs")
};

UCLASS()
class ASSIGNMENT1_API AStaircaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaircaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Properties")
	EStaircaseEnum StairType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int NumberOfSteps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	UStaticMesh* SourceMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Properties")
	FVector Dimensions;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Properties")
	FVector TranslationOffset;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Properties")
	TArray<UStaticMeshComponent*> StaticMeshComponents;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Properties")
	bool EnableRailing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (EditCondition = "EnableRailing"))
	UStaticMesh* RailingMesh;
};
