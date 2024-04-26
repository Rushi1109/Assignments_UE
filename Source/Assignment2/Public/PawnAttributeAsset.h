// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PawnAttributeAsset.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT2_API UPawnAttributeAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	float Speed;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax="100"))
	int Health;

	UPROPERTY(EditDefaultsOnly)
	float JumpHeight;
};
