// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainGameMode.h"
#include "GM_Basic.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API AGM_Basic : public AGameModeBase, public IINF_MainGameMode
{
	GENERATED_BODY()
	public:
    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> EndGameScreenClass;
    class UUserWidget* EndGameScreen;

    UFUNCTION(BlueprintNativeEvent)
    void SaveGame();
	virtual void SaveGame_Implementation();

    UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
    void LoadGame();
	virtual void LoadGame_Implementation();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
    void ReloadGame(bool bWithLastSave);
    virtual  void ReloadGame_Implementation(bool bWithLastSave);

    virtual void EndGame_Implementation();
};
