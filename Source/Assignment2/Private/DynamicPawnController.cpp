// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicPawnController.h"
#include "PawnDataTable.h"

void ADynamicPawnController::BeginPlay()
{
	SpawnActor();
}

void ADynamicPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Spawn", IE_Pressed, this, &ADynamicPawnController::SpawnActor);
}

ADynamicPawnController::ADynamicPawnController() : PawnIndex{0} {}

void ADynamicPawnController::SpawnActor()
{
	UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Assignment2/Assets/BP_PawnDataTable.BP_PawnDataTable'"));

	if (DataTable) {
		TArray<FName> RowNames = DataTable->GetRowNames();

		if (CurrentlySpawnedPawn) {
			CurrentlySpawnedPawn->Destroy();
			CurrentlySpawnedPawn = nullptr;
		}

		if (PawnIndex == RowNames.Num()) {
			PawnIndex = 0;
		}

		FPawnDataTable* PawnDataTableRow = DataTable->FindRow<FPawnDataTable>(RowNames[PawnIndex], TEXT("RowKey"));

		if (PawnDataTableRow) {
			TSubclassOf<APawn> PawnReference = PawnDataTableRow->PawnReference;
			EPawnType PawnType = PawnDataTableRow->PawnType;

			UE_LOG(LogTemp, Warning, TEXT("%s"), PawnDataTableRow->PawnReference);

			FActorSpawnParameters SpawnActorParams;
			SpawnActorParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			const FVector SpawnActorLocation(50, 50, 200);
			const FRotator SpawnActorRotation(0, 0, 0);

			APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnReference, SpawnActorLocation, SpawnActorRotation, SpawnActorParams);

			if (SpawnedPawn) {
				Possess(SpawnedPawn);
				CurrentlySpawnedPawn = SpawnedPawn;
				PawnIndex++;
			}
		}
	}
}
