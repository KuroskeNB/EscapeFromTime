// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainController.h"
#include "PC_MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API APC_MainCharacter : public APlayerController, public IINF_MainController
{
	GENERATED_BODY()
	public:
    
	virtual void BeginPlay() override;

    UFUNCTION(BlueprintNativeEvent)
    void InterfaceSetPause(bool Pause);
	virtual void InterfaceSetPause_Implementation(bool Pause) override;
	UFUNCTION(BlueprintNativeEvent)
    void InterfaceAddToViewport(TSubclassOf<class UUserWidget> WidgetClass);
	virtual void InterfaceAddToViewport_Implementation(TSubclassOf<class UUserWidget> WidgetClass) override;
	UFUNCTION(BlueprintNativeEvent)
    void InterfaceSetInputModeUIOnly();
	virtual void InterfaceSetInputModeUIOnly_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    void InterfaceSetInputModeGameOnly();
	virtual void InterfaceSetInputModeGameOnly_Implementation();

	virtual void OpenMenu_Implementation();
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainMenuClass;
	class UUserWidget* MainMenuWidget;
	bool bIsInMenu=false;

	private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainHudClass;
	class UUserWidget* MainHudWidget;

};
