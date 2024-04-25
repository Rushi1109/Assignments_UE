// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicPawnController.h"
#include "PawnDataTable.h"

void ADynamicPawnController::BeginPlay()
{
	SpawnActor();
}

ADynamicPawnController::ADynamicPawnController()
{
}

void ADynamicPawnController::SpawnActor()
{
	UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Assignment2/Assets/BP_PawnDataTable.BP_PawnDataTable'"));

	if (DataTable) {
		TArray<FName> RowNames = DataTable->GetRowNames();

		FPawnDataTable* PawnDataTableRow = DataTable->FindRow<FPawnDataTable>(RowNames[0], TEXT("RowKey"));

		if (PawnDataTableRow) {
			TSubclassOf<APawn> PawnReference = PawnDataTableRow->PawnReference;

			UE_LOG(LogTemp, Warning, TEXT("%s"), PawnDataTableRow->PawnReference);

			FActorSpawnParameters SpawnActorParams;
			SpawnActorParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			const FVector SpawnActorLocation(50, 50, 200);
			const FRotator SpawnActorRotation(0, 0, 0);

			APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnReference, SpawnActorLocation, SpawnActorRotation, SpawnActorParams);

			if (SpawnedPawn) {
				UE_LOG(LogTemp, Warning, TEXT("PAWN SPAWNED"));

				Possess(SpawnedPawn);
				
			}
		}
	}
}
