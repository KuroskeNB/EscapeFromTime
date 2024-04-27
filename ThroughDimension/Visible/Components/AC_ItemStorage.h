// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_ItemStorage.h"
#include "AC_ItemStorage.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemStorageUpdated, const FItemStorageData&,const float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THROUGHDIMENSION_API UAC_ItemStorage : public UActorComponent, public IINF_ItemStorage
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_ItemStorage();

/*
Interface functions
*/
UFUNCTION(BlueprintNativeEvent)
float GetSlowMoCount();
virtual float GetSlowMoCount_Implementation() override;
/*
Public properties
*/

struct FItemStorageData* CurrentExtraGadget;
class AActor* CurrentExtraGadgetMechanic;
class UUserWidget* CurrentExtraGadgetButton;
FOnItemStorageUpdated OnItemStorageUpdated;
TArray<struct FItemStorageData*>GadgetsInCD;
TArray<struct FItemStorageData*>GadgetsArray;
void InventoryOnItemStorageUpdated(const FItemStorageData& NewRow,const float Key);
//SlowMo
UPROPERTY(EditAnywhere, Category = "SlowMo")
float SlowMoMaximalCharge=1;
float SlowMoCharge;
UPROPERTY(EditAnywhere, Category = "SlowMo")
float SlowMoDelay=0.05;
UPROPERTY(EditAnywhere, Category = "SlowMo")
float SlowMoMomentCost=0.05;
void SlowMoUsed();
void SlowMo();
void SlowMoRecharge();
 UPROPERTY()
struct FTimerHandle SlowMoCDHandle;
void CooldownTimer(UTexture2D* StandardIcon,struct FItemStorageData* TempExtraGadget,class UUW_GadgetButton* TempGadgetButton);

bool bIsInSlowMo=false;
UPROPERTY(EditAnywhere)
class UDataTable* GadgetDataTable;
UFUNCTION(BlueprintNativeEvent)
FORCEINLINE class UDataTable* GetInventoryDataTable();
FORCEINLINE virtual class UDataTable* GetInventoryDataTable_Implementation() {return GadgetDataTable;}

/*
Item Storage UI
*/
UPROPERTY(EditAnywhere)
TSubclassOf<class UUserWidget> ItemStorageClass;
class UUW_ItemStorage* ItemStorageUI;
UPROPERTY(EditAnywhere)
TSubclassOf<class UUserWidget> InventoryClass;
class UUW_Inventory* InventoryUI;

/*
Stamina
*/

	UPROPERTY(EditAnywhere)
	float MaxStamina=100;
	float Stamina;
	UPROPERTY(EditAnywhere)
	float StrafeCost = 25;
    UFUNCTION()
	void StaminaUse(float Cost);
	UFUNCTION()
	void StaminaRestore();
	
	UPROPERTY()
	struct FTimerHandle StaminaRestoreTimer;
	UPROPERTY()
    struct FTimerHandle RestoreTimer;

	void StaminaRestoreTimerFunc();
/*
Functions
*/
UFUNCTION()
void NewGadget(const struct FItemStorageData& NewGadgetRow);
UFUNCTION()
void OpenInventory();
UFUNCTION()
void CloseInventory();
bool bInventoryIsOpen=false;
UFUNCTION()
void OnExtraGadgetChoosed( FItemStorageData& NewGadgetData, class UUserWidget* ButtonWidget);
UFUNCTION()
void UseExtraGadget();
UFUNCTION()
void ChooseGadgetWithKey(float Key);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
};
