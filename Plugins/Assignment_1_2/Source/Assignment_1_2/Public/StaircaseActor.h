// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaircaseActor.generated.h"

USTRUCT(BlueprintType)
struct FStaircaseStruct {
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    UStaticMeshComponent* FloorComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    UStaticMeshComponent* RailingLeftComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    UStaticMeshComponent* RailingRightComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    UStaticMeshComponent* HandrailLeftComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    UStaticMeshComponent* HandrailRightComponent;

    FStaircaseStruct();
};

UENUM()
enum class EStaircaseType : uint8 {
    ClosedStairs UMETA(DisplayName = "Closed Stairs"),
    OpenStairs UMETA(DisplayName = "Open Stairs"),
    BoxStairs UMETA(DisplayName = "Box Stairs")
};

UCLASS()
class ASSIGNMENT_1_2_API AStaircaseActor : public AActor {
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

    void DestroyStairs();
    void CreateStairs();

    UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Properties")
    EStaircaseType StairType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    int NumberOfSteps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    UStaticMesh* SourceMesh;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Properties")
    FVector Dimensions;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Properties",
              meta = (ClampMin = "100", UIMin = "100"))
    FVector TranslationOffset;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Properties")
    TArray<FStaircaseStruct> StaticMeshComponents;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Properties")
    bool EnableRailing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties",
              meta = (EditCondition = "EnableRailing"))
    UStaticMesh* RailingMesh;
};
