// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_GadgetButton.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGadgetButtonClickedWithParam, class UUW_GadgetButton*);
/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API UUW_GadgetButton : public UUserWidget
{
	GENERATED_BODY()
	public:
	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* TheButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ButtonKey;
	float ButtonKeyFloat;
	UPROPERTY()
	struct FItemStorageData FunctionalData;

    FOnGadgetButtonClickedWithParam OnGadgetButtonClickedWithParam;
	UFUNCTION()
    void OnTheButtonClicked();
	UFUNCTION()
	void SetButtonKey(float Key);
	UFUNCTION()
	void SetButtonIcon(UTexture2D* NewIcon);
	UFUNCTION()
	class UTexture2D* GetCurrentButtonIcon(){return CurrentIcon;}

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	private:
	class UTexture2D* CurrentIcon;
};
