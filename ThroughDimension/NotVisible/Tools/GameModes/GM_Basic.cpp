// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Basic.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/MainSaveGame.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/MainGameStateBase.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_CheckSavedActors.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/MainGameInstance.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemySoldier.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainController.h"
#include "TimerManager.h"

void AGM_Basic::SaveGame_Implementation()
{
     UMainSaveGame* SaveGameInstance = Cast<UMainSaveGame>(UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass()));
    if (SaveGameInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("save game"));
        // Заполните данные, которые вы хотите сохранить
        SaveGameInstance->PlayerLocation=UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation();
        SaveGameInstance->SavedDestroyedPawns=Cast<AMainGameStateBase>(GetWorld()->GetGameState())->GetSaveDestroyedPawns();
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, "SaveSlot", 0);
        for(auto ActorName:SaveGameInstance->SavedDestroyedPawns)
        {
            UE_LOG(LogTemp, Display, TEXT("actor saved to destroy %s"),*ActorName);
        }
        		UE_LOG(LogTemp, Warning, TEXT("saved player location %s"),*SaveGameInstance->PlayerLocation.ToString());
    }
}

void AGM_Basic::LoadGame_Implementation()
{
    UMainSaveGame* LoadedGame = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot", 0));
    if (LoadedGame)
    {
        Cast<AMainGameStateBase>(GetWorld()->GetGameState())->ReloadDestoyedPawns(LoadedGame->SavedDestroyedPawns);
        // Используйте данные, которые были загружены
       UGameplayStatics::GetPlayerPawn(GetWorld(),0)->SetActorLocation(LoadedGame->PlayerLocation);
       UE_LOG(LogTemp, Warning, TEXT("loaded player location %s"),*LoadedGame->PlayerLocation.ToString());
       TArray<AActor*> AllActors;
       UGameplayStatics::GetAllActorsWithInterface(GetWorld(),UINF_CheckSavedActors::StaticClass(),AllActors);
        for(auto ActorName:LoadedGame->SavedDestroyedPawns)
        {
            UE_LOG(LogTemp, Display, TEXT("actor saved to destroy %s"),*ActorName);
         for(auto Actor:AllActors)
         {
            if(Actor->GetActorNameOrLabel()==ActorName&& Actor->GetClass()->ImplementsInterface(UINF_EnemySoldier::StaticClass()))
            IINF_EnemySoldier::Execute_SetSpawnWeapon(Actor,false);
            if(Actor->GetActorNameOrLabel()==ActorName)
            Actor->Destroy();
         }
        }
    }
}

void AGM_Basic::ReloadGame_Implementation(bool bWithLastSave)
{   
    if(Cast<UMainGameInstance>(GetGameInstance()))
    {
    Cast<UMainGameInstance>(GetGameInstance())->bLoadWithSave=bWithLastSave;
    }
    FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
    GetWorld()->GetTimerManager().ClearAllTimersForObject(nullptr);
    UGameplayStatics::OpenLevel(GetWorld(), *CurrentLevelName, true);
}

void AGM_Basic::EndGame_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("end game"));
    if(EndGameScreenClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("you have widget class"));
     EndGameScreen=CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(),0),EndGameScreenClass);
     if(EndGameScreen &&UGameplayStatics::GetPlayerController(GetWorld(),0))
     {
         UE_LOG(LogTemp, Warning, TEXT("you have widget"));
		EndGameScreen->AddToViewport();
        if(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetClass()->ImplementsInterface(UINF_MainController::StaticClass()))
        IINF_MainController::Execute_InterfaceSetInputModeUIOnly(UGameplayStatics::GetPlayerController(GetWorld(),0));

     }
    }
}
