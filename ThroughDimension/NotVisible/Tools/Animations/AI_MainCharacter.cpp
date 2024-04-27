// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_MainCharacter.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"

bool UAI_MainCharacter::GetCharacterStandingStatus() 
{
    if(GetOwningActor()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    {
        return IINF_MainChar::Execute_GetStayingStatus(GetOwningActor());
    }
    return false;
}

bool UAI_MainCharacter::GetCharacterSlidingStatus()
{
    if(GetOwningActor()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    {
        return IINF_MainChar::Execute_GetSlidingStatus(GetOwningActor());
    }
    return false;
}

bool UAI_MainCharacter::GetCharacterLeaningStatus()
{
    if(GetOwningActor()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    {
        return IINF_MainChar::Execute_GetLeaningStatus(GetOwningActor());
    }
    return false;
}
