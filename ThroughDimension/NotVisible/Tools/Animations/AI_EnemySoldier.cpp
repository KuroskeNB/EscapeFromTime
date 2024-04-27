// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_EnemySoldier.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemyAiController.h"

bool UAI_EnemySoldier::GetEnemyTargetStatus()
{
    
    if(GetOwningActor()&&GetOwningActor()->GetInstigatorController()&&GetOwningActor()->GetInstigatorController()->GetClass()->ImplementsInterface(UINF_EnemyAiController::StaticClass()))
    {
        return IINF_EnemyAiController::Execute_GetHasTarget(GetOwningActor()->GetInstigatorController());
    }
    return false;
}

FRotator UAI_EnemySoldier::GetEnemyControlRotation()
{
    if(GetOwningActor()&&GetOwningActor()->GetInstigatorController()&&GetOwningActor()->GetInstigatorController()->GetClass()->ImplementsInterface(UINF_EnemyAiController::StaticClass()))
    {
        return IINF_EnemyAiController::Execute_GetAiControlRotation(GetOwningActor()->GetInstigatorController());
    }
    return FRotator();
}
