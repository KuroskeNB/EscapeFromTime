// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API UUW_MainHUD : public UUserWidget
{
	GENERATED_BODY()
	public:
	/*
	Properties
	*/
   UPROPERTY(meta = (BindWidgetOptional))
   class UTextBlock* Crosshair;
   UPROPERTY(meta = (BindWidgetOptional))
   class UTextBlock* AmmoCount;

   /*
   Functions
   */
  virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
};
