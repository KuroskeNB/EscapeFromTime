// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_ItemStorage.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API UUW_ItemStorage : public UUserWidget
{
	GENERATED_BODY()
	public:

	/*
	Properties
	*/
   UPROPERTY(meta = (BindWidgetOptional))
   class UImage* SlowMoImage;
   UPROPERTY(meta = (BindWidgetOptional))
   class UTextBlock* SlowMoCount;
   UPROPERTY(meta = (BindWidgetOptional))
   class UProgressBar* SlowMoCharge;
   UPROPERTY(meta = (BindWidgetOptional))
   class UProgressBar* StaminaCharge;
   UPROPERTY(meta = (BindWidgetOptional))
   class UImage* ExtraGadgetImage;
   UPROPERTY(meta = (BindWidgetOptional))
   class UTextBlock* GadgetCooldown;
   void SetExtraGadgetImage(class UTexture2D* Icon);
   void UpdateSlowMoCharge(float Charge);
   void UpdateStaminaCharge(float Charge);

   /*
   Functions
   */
  virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
};
