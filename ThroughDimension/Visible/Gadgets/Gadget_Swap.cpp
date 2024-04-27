// Fill out your copyright notice in the Description page of Project Settings.


#include "Gadget_Swap.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"
#include "Kismet/GameplayStatics.h"

void AGadget_Swap::UseGadget_Implementation()
{
    bIsInUsage=true;
    UE_LOG(LogTemp, Display, TEXT("swap"));
    FHitResult HitResult;
	FVector Location;
    FRotator Rotation;
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if(OwnerPawn->GetController() == nullptr) return;
    OwnerPawn->GetController()->GetPlayerViewPoint(Location,Rotation);
	FVector EndLocation =Location+ Rotation.Vector()*SwapDistance;
	FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(this);
    TraceParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,Location,EndLocation,ECC_Visibility,TraceParams);
    if(bHit && HitResult.GetActor()->ActorHasTag("Soldier") && OwnerPawn->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    {
        IINF_MainChar::Execute_InterfacePlayAnimation(GetOwner(),SwapAnimation,1.5);
        UE_LOG(LogTemp, Display, TEXT("swap with hit"));
        FVector LocationToSwap=HitResult.GetActor()->GetActorLocation();
        FRotator RotationToSwap=HitResult.GetActor()->GetActorRotation();
        HitResult.GetActor()->SetActorLocation(OwnerPawn->GetActorLocation());
        OwnerPawn->SetActorLocation(LocationToSwap);
        OwnerPawn->SetActorRotation(RotationToSwap);
        if(SwapParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),SwapParticle,OwnerPawn->GetActorLocation());
         bIsInUsage=false;
    }
    
}
