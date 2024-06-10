// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AMeshGenerator;

/**
 *
 */
class ASSIGNMENT_5_6_API FAsyncScatterTask : public FNonAbandonableTask {
public:
	FAsyncScatterTask(AMeshGenerator* InMeshGenerator);

	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(FAsyncScatterTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	void DoWork();

	FVector FindRandomPointInBox(FVector Origin, const FVector& ShapeDimensions);
	FVector FindRandomPointInSphere(FVector Origin, const FVector& ShapeDimensions);
private:
	AMeshGenerator* MeshGenerator;
};
