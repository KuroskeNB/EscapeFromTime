// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Inventory.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGadgetChoosed,  FItemStorageData&,UUserWidget*);
UCLASS()
class THROUGHDIMENSION_API UUW_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
FOnGadgetChoosed OnGadgetChoosed;

UPROPERTY(meta = (BindWidgetOptional))
   class UTextBlock* TestText;
UPROPERTY(meta = (BindWidgetOptional))
TArray<class UUserWidget*> GadgetButtons;
UPROPERTY(meta = (BindWidgetOptional))
class UWrapBox* MainWrapBox;
UPROPERTY(meta = (BindWidgetOptional))
class UWrapBox* KeyWrapBox;
UPROPERTY(EditAnywhere)
TSubclassOf<class UUserWidget> ButtonTemplate;

UFUNCTION()
void AddNewGadget();
UFUNCTION()
void AddNewButton(const FItemStorageData& NewRow, TSoftObjectPtr<UUserWidget> BindButtonPtr,const float Key);
UFUNCTION()
void OnGadgetButtonClicked(class UUW_GadgetButton* Button);
UFUNCTION()
void OpenInventory();
UFUNCTION()
class UUserWidget* GetGadgetButtonByKey(float Key){return GadgetButtons[Key];}

virtual void NativeConstruct() override;

void OnItemStorageUpdated(const FItemStorageData& NewRow,const float Key);

};
