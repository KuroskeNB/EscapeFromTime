// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemyAnimInstance.h"
#include "AI_EnemySoldier.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API UAI_EnemySoldier : public UAnimInstance
{
	GENERATED_BODY()
	private:
	
	UFUNCTION(BlueprintPure,BlueprintCallable, meta = (BlueprintThreadSafe))
	bool GetEnemyTargetStatus();
	UFUNCTION(BlueprintPure,BlueprintCallable, meta = (BlueprintThreadSafe))
	FRotator GetEnemyControlRotation();
};
