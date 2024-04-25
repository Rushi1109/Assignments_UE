// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DynamicPawnController.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT2_API ADynamicPawnController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	ADynamicPawnController();

	void SpawnActor();

private: 
	int PawnIndex;
	APawn* CurrentlySpawnedPawn;
};
