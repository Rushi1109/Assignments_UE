// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SMeshSelectionScrollBox.h"
#include "SlateOptMacros.h"
#include "Layout/Margin.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMeshSelectionScrollBox::Construct(const FArguments& InArgs) {
	ScrollBox = SNew(SScrollBox).Orientation(Orient_Horizontal);

	MeshAssetManager = InArgs._InMeshAssetManager;
	AssetType = InArgs._InAssetType;

	ChildSlot
	[
		ScrollBox.ToSharedRef()
	];
	
	LoadAssetInScrollBox();
}

void SMeshSelectionScrollBox::LoadAssetInScrollBox() {
	switch (AssetType) {
		case EAssetType::MaterialData:
			LoadMaterialData();
			break;

		case EAssetType::TextureData:
			LoadTextureData();
			break;

		default:
			LoadMeshData();
			break;
	}
}

void SMeshSelectionScrollBox::LoadMeshData() {
	ScrollBox->ClearChildren();

	if (MeshAssetManager.IsValid() && MeshAssetManager->MeshData.Num() > 0) {
		for (const FMeshData& MeshData : MeshAssetManager->MeshData) {
			TSharedPtr<SVerticalBox> VerticleBox = SNew(SVerticalBox);

			TSharedPtr<SBox> SizeBox = SNew(SBox);
			SizeBox->SetWidthOverride(TAttribute<FOptionalSize>{125.f});
			SizeBox->SetHeightOverride(TAttribute<FOptionalSize>{125.f});
			SizeBox->SetPadding(FMargin{ 5.f });

			FSlateColorBrush* Brush = new FSlateColorBrush(FLinearColor{ 0.208745, 0.788352, 1.0 });
			TSharedPtr<SBorder> BorderBox = SNew(SBorder).BorderImage(Brush);

			if (MeshData.MeshThumbnail) {
				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->DrawAs = ESlateBrushDrawType::RoundedBox;

				FSlateBrushOutlineSettings OutlineSettings{};
				OutlineSettings.CornerRadii = FVector4{ 5.f };
				OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
				ThumbnailBrush->OutlineSettings = OutlineSettings;
				
				ThumbnailBrush->SetResourceObject(MeshData.MeshThumbnail);
				ThumbnailBrush->SetImageSize(FVector2D(MeshData.MeshThumbnail->GetSizeX(), MeshData.MeshThumbnail->GetSizeY()));

				TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).Cursor(EMouseCursor::Hand)
					.OnMouseButtonDown_Lambda(
						[this, MeshData](const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
							if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
								// TODO: Execute the delegate
								return FReply::Handled();
							}

							return FReply::Unhandled();
						}
				);

				TSharedPtr<STextBlock> ThumbnailName = SNew(STextBlock).Text(FText::FromString(MeshData.MeshName)).ColorAndOpacity(FLinearColor{ 0.f, 0.f, 0.f });

				BorderBox->SetContent(ThumbnailImage.ToSharedRef());
				SizeBox->SetContent(BorderBox.ToSharedRef());

				VerticleBox->AddSlot().Padding(FMargin{ 5.f })
					[
						SizeBox.ToSharedRef()
					];
				VerticleBox->AddSlot().HAlign(HAlign_Center).FillHeight(0.2)
					[
						ThumbnailName.ToSharedRef()
					];

				ScrollBox->AddSlot()
					[
						VerticleBox.ToSharedRef()
					];
			}
		}
	}
}

void SMeshSelectionScrollBox::LoadMaterialData() {
	ScrollBox->ClearChildren();

	if (MeshAssetManager.IsValid() && MeshAssetManager->MaterialData.Num() > 0) {
		for (const FMaterialData& MaterialData : MeshAssetManager->MaterialData) {
			TSharedPtr<SVerticalBox> VerticleBox = SNew(SVerticalBox);

			TSharedPtr<SBox> SizeBox = SNew(SBox);
			SizeBox->SetWidthOverride(TAttribute<FOptionalSize>{125.f});
			SizeBox->SetHeightOverride(TAttribute<FOptionalSize>{125.f});

			FSlateColorBrush* Brush = new FSlateColorBrush(FLinearColor{ 0.208745, 0.788352, 1.0 });
			TSharedPtr<SBorder> BorderBox = SNew(SBorder).BorderImage(Brush);

			if (MaterialData.MaterialThumbnail) {
				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(MaterialData.MaterialThumbnail);
				ThumbnailBrush->SetImageSize(FVector2D(MaterialData.MaterialThumbnail->GetSizeX(), MaterialData.MaterialThumbnail->GetSizeY()));

				TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).Cursor(EMouseCursor::Hand)
					.OnMouseButtonDown_Lambda(
						[this, MaterialData](const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
							if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
								// TODO: Execute the delegate
								return FReply::Handled();
							}

							return FReply::Unhandled();
						}
				);;

				TSharedPtr<STextBlock> ThumbnailName = SNew(STextBlock).Text(FText::FromString(MaterialData.MaterialName)).ColorAndOpacity(FLinearColor{ 0.f, 0.f, 0.f });

				BorderBox->SetContent(ThumbnailImage.ToSharedRef());
				SizeBox->SetContent(BorderBox.ToSharedRef());

				VerticleBox->AddSlot().Padding(FMargin{ 5.f })
					[
						SizeBox.ToSharedRef()
					];
				VerticleBox->AddSlot().HAlign(HAlign_Center).FillHeight(0.2)
					[
						ThumbnailName.ToSharedRef()
					];

				ScrollBox->AddSlot()
					[
						VerticleBox.ToSharedRef()
					];
			}
		}
	}
}

void SMeshSelectionScrollBox::LoadTextureData() {
	ScrollBox->ClearChildren();

	if (MeshAssetManager.IsValid() && MeshAssetManager->TextureData.Num() > 0) {
		for (const FTextureData& TextureData : MeshAssetManager->TextureData) {
			TSharedPtr<SVerticalBox> VerticleBox = SNew(SVerticalBox);

			TSharedPtr<SBox> SizeBox = SNew(SBox);
			SizeBox->SetWidthOverride(TAttribute<FOptionalSize>{125.f});
			SizeBox->SetHeightOverride(TAttribute<FOptionalSize>{125.f});

			FSlateColorBrush* Brush = new FSlateColorBrush(FLinearColor{ 0.208745, 0.788352, 1.0 });
			TSharedPtr<SBorder> BorderBox = SNew(SBorder).BorderImage(Brush);

			if (UTexture2D* TextureIcon = Cast<UTexture2D>(TextureData.TextureAsset)) {
				FSlateBrush* ThumbnailBrush = new FSlateBrush();
				ThumbnailBrush->SetResourceObject(TextureData.TextureAsset);
				ThumbnailBrush->SetImageSize(FVector2D(TextureIcon->GetSizeX(), TextureIcon->GetSizeY()));

				TSharedPtr<SImage> ThumbnailImage = SNew(SImage).Image(ThumbnailBrush).Cursor(EMouseCursor::Hand)
					.OnMouseButtonDown_Lambda(
						[this, TextureData](const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) {
							if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
								// TODO: Execute the delegate
								return FReply::Handled();
							}

							return FReply::Unhandled();
						}
				);;

				TSharedPtr<STextBlock> ThumbnailName = SNew(STextBlock).Text(FText::FromString(TextureData.TextureName)).ColorAndOpacity(FLinearColor{0.f, 0.f, 0.f});

				BorderBox->SetContent(ThumbnailImage.ToSharedRef());
				SizeBox->SetContent(BorderBox.ToSharedRef());

				VerticleBox->AddSlot().Padding(FMargin{ 5.f })
					[
						SizeBox.ToSharedRef()
					];
				VerticleBox->AddSlot().HAlign(HAlign_Center).FillHeight(0.2)
					[
						ThumbnailName.ToSharedRef()
					];

				ScrollBox->AddSlot()
					[
						VerticleBox.ToSharedRef()
					];
			}
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
