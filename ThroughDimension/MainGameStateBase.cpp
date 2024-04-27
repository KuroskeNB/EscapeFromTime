// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameStateBase.h"

void AMainGameStateBase::AddDestroyedPawn(FString PawnName)
{
    SaveDestroyedPawns.Add(PawnName);
}

void AMainGameStateBase::CheckDestroyedPawns()
{
    for(const FString& Name:SaveDestroyedPawns)
    {
     UE_LOG(LogTemp, Warning, TEXT("DestroyedPawn%s"),*Name);
    }
}
