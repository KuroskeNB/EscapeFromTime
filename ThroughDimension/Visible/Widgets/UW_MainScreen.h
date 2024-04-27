// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_MainScreen.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API UUW_MainScreen : public UUserWidget
{
	GENERATED_BODY()
	public:
    UPROPERTY(meta = (BindWidgetOptional))
	class UButton* RestartWithSave;
	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* RestartFromBegining;
	UPROPERTY(meta = (BindWidgetOptional))
	class UButton* Exit;
    
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnWithSaveClicked();
    UFUNCTION()
	void OnFromBeginingClicked();
	UFUNCTION()
	void OnExitClicked();

};
