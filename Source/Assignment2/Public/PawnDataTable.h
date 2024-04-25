// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PawnDataTable.generated.h"


UENUM(BlueprintType)
enum class EPawnType : uint8 {
	ThirdPerson UMETA(DisplayName = "Third Person"),
	TopDown UMETA(DisplayName = "Top Down")
};

USTRUCT(BlueprintType)
struct FPawnDataTable : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPawnType PawnType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> PawnReference;

	FPawnDataTable();
};

/**
 * 
 */
class ASSIGNMENT2_API PawnDataTable
{
public:
	PawnDataTable();
	~PawnDataTable();
};
