// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "INF_GadgetMechanic.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UINF_GadgetMechanic : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THROUGHDIMENSION_API IINF_GadgetMechanic
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

UFUNCTION(BlueprintNativeEvent)
void UseGadget();
UFUNCTION(BlueprintNativeEvent)
void CustomDestroy();
UFUNCTION(BlueprintNativeEvent)
bool GetInUsageStatus();
};
