// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemStorageData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct THROUGHDIMENSION_API FItemStorageData : public FTableRowBase
{
GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	class UTexture2D* Icon;
	UPROPERTY(EditAnywhere)
	class UTexture2D* CDIcon;
	UPROPERTY(EditAnywhere)
	FName GadgetName;
	UPROPERTY(EditAnywhere)
	float CooldownTime;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> GadgetMechanic;
	UPROPERTY(EditAnywhere)
	bool bIsUnlocked;
	UPROPERTY(EditAnywhere)
	float CDTime=5;
};
