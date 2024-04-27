// Fill out your copyright notice in the Description page of Project Settings.


#include "Gadget_Shield.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"
#include "TimerManager.h"

void AGadget_Shield::UseGadget_Implementation()
{
    if(ShieldClass && GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()) && !bIsInUsage)
    {
     bIsInUsage=true;
     UE_LOG(LogTemp, Display, TEXT("uage status set to true %d"),bIsInUsage);
     IINF_MainChar::Execute_SetUsingGadget(GetOwner(),bIsInUsage);
    Shield=GetWorld()->SpawnActor<AActor>(ShieldClass);
    IINF_MainChar::Execute_AttachToInteractComponent(GetOwner(),Shield);
    IINF_MainChar::Execute_InterfacePlayAnimation(GetOwner(),ShieldAnimation,0);
    }
    else if(bIsInUsage)
    {
    if(Shield)
    {
        Shield->Destroy();
    }
    if(GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    {
     IINF_MainChar::Execute_InterfaceStopAllMontages(GetOwner());
    }
    bIsInUsage=false;
    IINF_MainChar::Execute_SetUsingGadget(GetOwner(),bIsInUsage);
    }
}

void AGadget_Shield::CustomDestroy_Implementation()
{
    if(Shield)
    {
        Shield->Destroy();
    }
    if(GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    {
     IINF_MainChar::Execute_InterfaceStopAllMontages(GetOwner());
    }
    bIsInUsage=false;
    IINF_MainChar::Execute_SetUsingGadget(GetOwner(),bIsInUsage);
    Destroy();
}

bool AGadget_Shield::GetInUsageStatus_Implementation()
{
 UE_LOG(LogTemp, Display, TEXT("get in uage status %d"),bIsInUsage);
	return bIsInUsage;
}
