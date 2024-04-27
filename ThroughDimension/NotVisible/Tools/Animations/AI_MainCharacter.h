// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API UAI_MainCharacter : public UAnimInstance
{
	GENERATED_BODY()
	private:
	
	UFUNCTION(BlueprintPure,BlueprintCallable, meta = (BlueprintThreadSafe))
	bool GetCharacterStandingStatus();
	UFUNCTION(BlueprintPure,BlueprintCallable, meta = (BlueprintThreadSafe))
	bool GetCharacterSlidingStatus();
	UFUNCTION(BlueprintPure,BlueprintCallable, meta = (BlueprintThreadSafe))
	bool GetCharacterLeaningStatus();
};
