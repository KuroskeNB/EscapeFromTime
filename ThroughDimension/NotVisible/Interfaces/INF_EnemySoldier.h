// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "INF_EnemySoldier.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UINF_EnemySoldier : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THROUGHDIMENSION_API IINF_EnemySoldier
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
UFUNCTION(BlueprintNativeEvent)
FORCEINLINE AActor* GetGun();
UFUNCTION(BlueprintNativeEvent)
void EnemyShoot();
UFUNCTION(BlueprintNativeEvent)
void InterfacePlayAnimation(class UAnimMontage* AnimMontage,float PlayRate);
UFUNCTION(BlueprintNativeEvent)
void SetSpawnWeapon(bool ShouldSpawn);
UFUNCTION(BlueprintNativeEvent)
float GetSoldierShootRange();
};
