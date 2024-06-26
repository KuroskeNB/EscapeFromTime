// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MainSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()
	public:
	UPROPERTY()
	FVector PlayerLocation;
	UPROPERTY()
	TArray<FString> SavedDestroyedPawns;
};
