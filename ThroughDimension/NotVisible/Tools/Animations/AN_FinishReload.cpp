// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_FinishReload.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_Gun.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemySoldier.h"


void UAN_FinishReload::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    if(MeshComp&&MeshComp->GetOwner()&& MeshComp->GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
 {
    UE_LOG(LogTemp, Display, TEXT("reloading"));
   IINF_Gun::Execute_FinishReload(IINF_MainChar::Execute_GetGun(MeshComp->GetOwner()));
 }
  if(MeshComp&&MeshComp->GetOwner()&& MeshComp->GetOwner()->GetClass()->ImplementsInterface(UINF_EnemySoldier::StaticClass()))
 {
   IINF_Gun::Execute_FinishReload(IINF_EnemySoldier::Execute_GetGun(MeshComp->GetOwner()));
 }
}
