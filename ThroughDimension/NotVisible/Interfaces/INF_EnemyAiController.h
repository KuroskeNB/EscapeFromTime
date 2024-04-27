// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "INF_EnemyAiController.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UINF_EnemyAiController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THROUGHDIMENSION_API IINF_EnemyAiController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
UFUNCTION(BlueprintNativeEvent)
FORCEINLINE bool GetHasTarget();
UFUNCTION(BlueprintNativeEvent)
FRotator GetAiControlRotation();
UFUNCTION(BlueprintNativeEvent)
FORCEINLINE float GetAiControlPitchRotation();
UFUNCTION(BlueprintNativeEvent)
void AiCustomDestroy();
UFUNCTION(BlueprintNativeEvent)
void SetTargetLocation(FVector Location);

};
