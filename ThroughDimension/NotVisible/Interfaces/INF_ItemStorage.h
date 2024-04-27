// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "INF_ItemStorage.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UINF_ItemStorage : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THROUGHDIMENSION_API IINF_ItemStorage
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

UFUNCTION(BlueprintNativeEvent)
float GetSlowMoCount();

UFUNCTION(BlueprintNativeEvent)
FORCEINLINE class UDataTable* GetInventoryDataTable();
};
