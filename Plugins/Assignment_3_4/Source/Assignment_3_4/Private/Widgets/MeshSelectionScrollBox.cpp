// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MeshSelectionScrollBox.h"

TSharedRef<SWidget> UMeshSelectionScrollBox::RebuildWidget() {
	MeshSelectionScrollBox = SNew(SMeshSelectionScrollBox).InMeshAssetManager(MeshAssetManager).InAssetType(ScrollBoxAssetType);
	MeshSelectionScrollBox->OnMeshAssetSelected.BindUFunction(this, "HandleMeshAssetReceived");
	MeshSelectionScrollBox->OnMaterialAssetSelected.BindUFunction(this, "HandleMaterialAssetReceived");
	MeshSelectionScrollBox->OnTextureAssetSelected.BindUFunction(this, "HandleTextureAssetReceived");

	TSharedPtr<SScrollBox> ScrollBox = SNew(SScrollBox).Orientation(Orient_Vertical);
	TSharedPtr<STextBlock> TitleText = SNew(STextBlock).Text(GetTitleTextFromEnum());
	FSlateColorBrush* Brush = new FSlateColorBrush(FLinearColor{ 1.f, 1.f, 1.f });
	TSharedPtr<SBorder> BorderBox = SNew(SBorder).BorderImage(Brush);

	FSlateFontInfo FontInfo = GetFontInfo();
	FontInfo.Size = 24.f;
	TitleText->SetFont(FontInfo);
	TitleText->SetColorAndOpacity(FSlateColor{ FLinearColor{0.f, 0.f, 0.f} });

	ScrollBox->AddSlot().FillSize(0.2).HAlign(HAlign_Center)
	[
		TitleText.ToSharedRef()
	];
	ScrollBox->AddSlot()	
	[
		MeshSelectionScrollBox.ToSharedRef()
	];

	BorderBox->SetContent(ScrollBox.ToSharedRef());

	return BorderBox.ToSharedRef();
}

const FText UMeshSelectionScrollBox::GetTitleTextFromEnum() {
	switch (ScrollBoxAssetType) {
	case EAssetType::MeshData:
		return FText::FromString("Mesh Asset");
		break;
	case EAssetType::MaterialData:
		return FText::FromString("Material Asset");
		break;
	case EAssetType::TextureData:
		return FText::FromString("Texture Asset");
		break;
	default:
		return FText::FromString("Default Title");
		break;
	}
}

void UMeshSelectionScrollBox::ReleaseSlateResources(bool bReleaseChildren) {
	Super::ReleaseSlateResources(bReleaseChildren);

	MeshSelectionScrollBox.Reset();
}

const FText UMeshSelectionScrollBox::GetPaletteCategory() {
	return FText::FromString("Panel");
}

void UMeshSelectionScrollBox::SynchronizeProperties() {
    Super::SynchronizeProperties();

    if (MeshSelectionScrollBox.IsValid()) {
        MeshSelectionScrollBox->MeshAssetManager = MeshAssetManager;
        MeshSelectionScrollBox->LoadAssetInScrollBox();
    }
}

void UMeshSelectionScrollBox::HandleMeshAssetReceived(const FMeshData& MeshData) {
	OnMeshAssetReceived.ExecuteIfBound(MeshData);
}

void UMeshSelectionScrollBox::HandleMaterialAssetReceived(const FMaterialData& MaterialData) {
	OnMaterialAssetReceived.ExecuteIfBound(MaterialData);
}

void UMeshSelectionScrollBox::HandleTextureAssetReceived(const FTextureData& TextureData) {
	OnTextureAssetReceived.ExecuteIfBound(TextureData);
}

TSharedPtr<SMeshSelectionScrollBox> UMeshSelectionScrollBox::GetMeshSelectionScrollBox() {
	return MeshSelectionScrollBox;
}
