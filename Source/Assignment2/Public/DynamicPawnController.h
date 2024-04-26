// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnDataTable.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "PawnAttributeAsset.h"
#include "BaseCharacter.h"
#include "FirstPersonPawn.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputMappingContext* PawnMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* SwapAction;

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayAttributes(UPawnAttributeAsset* PawnAttributeAsset);

private: 
	int PawnIndex;
	APawn* CurrentSpawnedPawn;
	EPawnType CurrentPawnType;
	UDataTable* DataTable;
};
