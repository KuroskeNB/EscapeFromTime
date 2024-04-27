// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
UPROPERTY(EditAnywhere)
bool bLoadWithSave=false;
UFUNCTION(BlueprintCallable)
bool GetLoadWithSave(){return bLoadWithSave;};
UFUNCTION(BlueprintCallable)
void SetLoadWithSave(bool YesOrNo){bLoadWithSave=YesOrNo;};
};
