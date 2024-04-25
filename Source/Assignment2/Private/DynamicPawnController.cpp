// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicPawnController.h"
#include "GameFramework/GameModeBase.h"

void ADynamicPawnController::BeginPlay()
{
	SpawnActor();
}

void ADynamicPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Spawn", IE_Pressed, this, &ADynamicPawnController::SpawnActor);
}

ADynamicPawnController::ADynamicPawnController() : PawnIndex{ 0 }, CurrentSpawnedPawn{ nullptr } {
	DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Assignment2/Assets/BP_PawnDataTable.BP_PawnDataTable'"));
}

void ADynamicPawnController::SpawnActor()
{
	if (DataTable) {
		TArray<FName> RowNames = DataTable->GetRowNames();

		if (CurrentSpawnedPawn) {
			CurrentSpawnedPawn->Destroy();
			CurrentSpawnedPawn = nullptr;
		}

		FPawnDataTable* PawnDataTableRow = DataTable->FindRow<FPawnDataTable>(RowNames[PawnIndex], TEXT("RowKey"));

		if (PawnDataTableRow) {
			TSubclassOf<APawn> PawnReference = PawnDataTableRow->PawnReference;
			CurrentPawnType = PawnDataTableRow->PawnType;

			FActorSpawnParameters SpawnActorParams;
			SpawnActorParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			const FVector SpawnActorLocation(50, 50, 200);
			const FRotator SpawnActorRotation(0, 0, 0);

			APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnReference, SpawnActorLocation, SpawnActorRotation, SpawnActorParams);

			if (SpawnedPawn) {
				Possess(SpawnedPawn);
				
				CurrentSpawnedPawn = SpawnedPawn;
				PawnIndex = (PawnIndex+1)%RowNames.Num();

				if (CurrentPawnType == EPawnType::TopDown) {
					SetShowMouseCursor(true);
				}
				else {
					SetShowMouseCursor(false);
				}
			}
		}
	}
}
