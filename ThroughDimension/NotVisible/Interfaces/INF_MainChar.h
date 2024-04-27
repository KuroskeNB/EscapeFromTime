// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "INF_MainChar.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UINF_MainChar : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THROUGHDIMENSION_API IINF_MainChar
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
bool GetStayingStatus();
UFUNCTION(BlueprintNativeEvent)
bool GetSlidingStatus();
UFUNCTION(BlueprintNativeEvent)
bool GetLeaningStatus();
UFUNCTION(BlueprintNativeEvent)
bool GetAliveStatus();
UFUNCTION(BlueprintNativeEvent)
void Sliding();
UFUNCTION(BlueprintNativeEvent)
void InterfaceJump();
UFUNCTION(BlueprintNativeEvent)
void EndSliding();
UFUNCTION(BlueprintNativeEvent)
FORCEINLINE UObject* GetItemStorage();
UFUNCTION(BlueprintNativeEvent)
AActor* GetGun();
UFUNCTION(BlueprintNativeEvent)
FORCEINLINE class AController* GetCharacterController();
UFUNCTION(BlueprintNativeEvent)
void InterfacePlayAnimation(class UAnimMontage* AnimMontage,float PlayRate);
UFUNCTION(BlueprintNativeEvent)
void InterfaceGetViewPoint(FVector& outLocation, FRotator& outRotation);
UFUNCTION(BlueprintNativeEvent)
void AttachToInteractComponent(AActor* Item);
UFUNCTION(BlueprintNativeEvent)
void InterfaceStopAllMontages();
UFUNCTION(BlueprintNativeEvent)
void SetUsingGadget(bool bIsUsing);
UFUNCTION(BlueprintNativeEvent)
void SetClingingStatus(bool status);

};
