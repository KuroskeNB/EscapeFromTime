// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_Sliding.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"

void UANS_Sliding::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime)
{
    if(MeshComp->GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()) && FVector::Dist(StartPosition,MeshComp->GetOwner()->GetActorLocation())>700)
    {
        IINF_MainChar::Execute_Sliding(MeshComp->GetOwner());
    }
    else
    {
        
    }
}

void UANS_Sliding::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    StartPosition=MeshComp->GetOwner()->GetActorLocation();
}

void UANS_Sliding::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
    MeshComp->GetOwner()->SetActorLocation(MeshComp->GetComponentLocation());
    UE_LOG(LogTemp, Display, TEXT("Mesh loc %u"),MeshComp->GetComponentLocation());
    UE_LOG(LogTemp, Display, TEXT("Capsule loc %u"),MeshComp->GetOwner()->GetActorLocation());
}
