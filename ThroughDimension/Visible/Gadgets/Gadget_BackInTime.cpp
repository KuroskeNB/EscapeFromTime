// Fill out your copyright notice in the Description page of Project Settings.


#include "Gadget_BackInTime.h"
#include "Kismet/GameplayStatics.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"


void AGadget_BackInTime::UseGadget_Implementation()
{
    UE_LOG(LogTemp, Display, TEXT("use back in time"));
    if(!bIsInUsage)
    {
    SaveLocation=GetOwner()->GetActorLocation();
     if(TimeParticle)
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),TimeParticle,GetOwner()->GetActorLocation());
    bIsInUsage=true;
    }
    else
    {
    GetOwner()->SetActorLocation(SaveLocation);
    if(GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    IINF_MainChar::Execute_InterfaceStopAllMontages(GetOwner());
    if(TimeParticle)
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),TimeParticle,GetOwner()->GetActorLocation());
    bIsInUsage=false;
    }
}

void AGadget_BackInTime::CustomDestroy_Implementation()
{
    Destroy();
}
