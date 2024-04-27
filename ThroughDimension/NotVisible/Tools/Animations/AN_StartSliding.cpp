// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_StartSliding.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"

void UAN_StartSliding::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
 if(MeshComp&&MeshComp->GetOwner()&& MeshComp->GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
 {
    UE_LOG(LogTemp, Display, TEXT("an start sliding"));
   IINF_MainChar::Execute_Sliding(MeshComp->GetOwner());
 }
}
