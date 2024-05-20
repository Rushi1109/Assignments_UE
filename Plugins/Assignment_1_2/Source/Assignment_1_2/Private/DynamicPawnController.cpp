// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicPawnController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void ADynamicPawnController::BeginPlay()
{
	Super::BeginPlay();
}

void ADynamicPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast< UEnhancedInputComponent>(InputComponent)) {
		EIC->BindAction(SwapAction, ETriggerEvent::Completed, this, &ADynamicPawnController::SpawnActor);
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
		Subsystem->AddMappingContext(PawnMappingContext, 0);
	}
}

ADynamicPawnController::ADynamicPawnController() : PawnIndex{ 0 }, CurrentSpawnedPawn{ nullptr } {}

void ADynamicPawnController::SpawnActor()
{	
	DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Assignment_1_2/Assets/BP_PawnDataTable.BP_PawnDataTable'"));
	if (DataTable) {
		TArray<FName> RowNames = DataTable->GetRowNames();

		FPawnDataTable* PawnDataTableRow = DataTable->FindRow<FPawnDataTable>(RowNames[PawnIndex], TEXT("RowKey"));

		FVector SpawnActorLocation;
		FRotator SpawnActorRotation;

		if (CurrentSpawnedPawn) {
			SpawnActorLocation = CurrentSpawnedPawn->GetActorLocation();
			SpawnActorRotation = CurrentSpawnedPawn->GetActorRotation();

			CurrentSpawnedPawn->Destroy();
			CurrentSpawnedPawn = nullptr;
		}
		else {
			SpawnActorLocation = FVector{ 0, 0, 50 };
			SpawnActorRotation = FRotator{ 0, 0, 0 };
		}

		if (PawnDataTableRow) {
			TSubclassOf<APawn> PawnReference = PawnDataTableRow->PawnReference;
			CurrentPawnType = PawnDataTableRow->PawnType;

			FActorSpawnParameters SpawnActorParams;
			SpawnActorParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
				Subsystem->ClearAllMappings();
			}
			
			APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PawnReference, SpawnActorLocation, SpawnActorRotation, SpawnActorParams);

			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
				Subsystem->AddMappingContext(PawnMappingContext, 0);
			}

			if (SpawnedPawn) {
				Possess(SpawnedPawn);
	
				CurrentSpawnedPawn = SpawnedPawn;
				PawnIndex = (PawnIndex+1)%RowNames.Num();

				if (CurrentPawnType == EPawnType::TopDown) {
					SetShowMouseCursor(true);
					DisplayAttributes(Cast<ABaseCharacter>(SpawnedPawn)->PawnAttributeAsset);
				}
				else if(CurrentPawnType == EPawnType::FirstPerson){
					SetShowMouseCursor(false);
					DisplayAttributes(Cast<AFirstPersonPawn>(SpawnedPawn)->PawnAttributeAsset);
				}
				else {
					SetShowMouseCursor(false);
					DisplayAttributes(Cast<ABaseCharacter>(SpawnedPawn)->PawnAttributeAsset);
				}
			}
		}
	}
}
