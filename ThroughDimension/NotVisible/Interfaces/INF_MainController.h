// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "INF_MainController.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UINF_MainController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THROUGHDIMENSION_API IINF_MainController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
UFUNCTION(BlueprintNativeEvent)
void InterfaceSetPause(bool Pause);
UFUNCTION(BlueprintNativeEvent)
void InterfaceAddToViewport(TSubclassOf<class UUserWidget> WidgetClass);
UFUNCTION(BlueprintNativeEvent)
void InterfaceSetInputModeUIOnly();
UFUNCTION(BlueprintNativeEvent)
void InterfaceSetInputModeGameOnly();
UFUNCTION(BlueprintNativeEvent)
void OpenMenu();
};
