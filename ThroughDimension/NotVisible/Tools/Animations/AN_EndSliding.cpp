// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_EndSliding.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"


void UAN_EndSliding::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
 if(MeshComp->GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
 {
   IINF_MainChar::Execute_EndSliding(MeshComp->GetOwner());
 }
}
