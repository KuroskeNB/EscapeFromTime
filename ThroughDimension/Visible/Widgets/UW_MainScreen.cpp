// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_MainScreen.h"
#include "Components/Button.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/MainGameInstance.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainGameMode.h"
#include "GameFramework/GameModeBase.h"

void UUW_MainScreen::NativeConstruct()
{
    Super::NativeConstruct();
    if(RestartWithSave)
    {
        RestartWithSave->OnPressed.AddDynamic(this,&UUW_MainScreen::OnWithSaveClicked);
    }
    if(RestartFromBegining)
    {
        RestartFromBegining->OnPressed.AddDynamic(this,&UUW_MainScreen::OnFromBeginingClicked);
    }
    if(Exit)
    {
        Exit->OnPressed.AddDynamic(this,&UUW_MainScreen::OnExitClicked);
    }
}

void UUW_MainScreen::OnWithSaveClicked()
{
    Cast<UMainGameInstance>(GetWorld()->GetGameInstance())->SetLoadWithSave(true);
    if(GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(UINF_MainGameMode::StaticClass()))
    {
     IINF_MainGameMode::Execute_ReloadGame(GetWorld()->GetAuthGameMode(),true);
    }
}

void UUW_MainScreen::OnFromBeginingClicked()
{
    Cast<UMainGameInstance>(GetWorld()->GetGameInstance())->SetLoadWithSave(false);
    if(GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(UINF_MainGameMode::StaticClass()))
    {
     IINF_MainGameMode::Execute_ReloadGame(GetWorld()->GetAuthGameMode(),false);
    }
}

void UUW_MainScreen::OnExitClicked()
{
}
