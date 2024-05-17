// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/Public/Components/CanvasPanel.h"
#include "MeshSelectionScrollBox.h"
#include "SelectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT4_API USelectionWidget : public UUserWidget {
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Canvas;

	UPROPERTY(meta = (BindWidget))
	UMeshSelectionScrollBox* ScrollBox1;

	UPROPERTY(meta = (BindWidget))
	UMeshSelectionScrollBox* ScrollBox2;

	UPROPERTY(meta = (BindWidget))
	UMeshSelectionScrollBox* ScrollBox3;

	virtual void NativeConstruct() override;
};
