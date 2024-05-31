// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VerticalRailActor.h"
#include "Engine/DataAsset.h"
#include "VerticleRailAsset.generated.h"

USTRUCT(Blueprintable)
struct FVerticalRailData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* RailStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AVerticalRailActor> RailClassRef;
};

/**
 *
 */
UCLASS()
class ASSIGNMENT_5_6_API UVerticleRailAsset : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<ERailTopType, FVerticalRailData> RailDataMap;
};
