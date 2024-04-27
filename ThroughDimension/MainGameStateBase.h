// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API AMainGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	public:
	TArray<FString> SaveDestroyedPawns;
	TArray<FString> GetSaveDestroyedPawns(){return SaveDestroyedPawns;};
	void AddDestroyedPawn(FString PawnName);
	void ReloadDestoyedPawns(TArray<FString> ReloadPawns){SaveDestroyedPawns=ReloadPawns;};
	void CheckDestroyedPawns();
};
