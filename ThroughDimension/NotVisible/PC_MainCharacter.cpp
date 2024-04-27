// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_MainCharacter.h"
#include "Blueprint/UserWidget.h"


void APC_MainCharacter::InterfaceSetPause_Implementation(bool Pause)
{
    SetPause(Pause);
}

void APC_MainCharacter::InterfaceAddToViewport_Implementation(TSubclassOf<class UUserWidget> WidgetClass)
{
  
}

void APC_MainCharacter::InterfaceSetInputModeUIOnly_Implementation()
{
    FInputModeGameAndUI UiOnly;
    SetInputMode(UiOnly);
    SetShowMouseCursor(true);
}

void APC_MainCharacter::InterfaceSetInputModeGameOnly_Implementation()
{
    FInputModeGameOnly GameOnly;
    SetInputMode(GameOnly);
    SetShowMouseCursor(false);
}

void APC_MainCharacter::OpenMenu_Implementation()
{
    if(MainMenuClass &&!bIsInMenu)
    {
        MainMenuWidget=CreateWidget(this,MainMenuClass);
        if(MainMenuWidget)
        MainMenuWidget->AddToViewport();
        FInputModeUIOnly UIOnly;
        SetInputMode(UIOnly);
        SetShowMouseCursor(true);
         bIsInMenu=true;
    }
    else if(bIsInMenu)
    {
        if(MainMenuWidget)
        MainMenuWidget->RemoveFromParent();
        FInputModeGameOnly GameOnly;
        SetInputMode(GameOnly);
        SetShowMouseCursor(false);
               bIsInMenu=false;
    }
}

void APC_MainCharacter::BeginPlay()
{
    Super::BeginPlay();
    if(MainHudClass)
    {
        MainHudWidget=CreateWidget(this,MainHudClass);
        if(MainHudWidget)
        MainHudWidget->AddToViewport();
    }
    InterfaceSetInputModeGameOnly_Implementation();
}
