// Fill out your copyright notice in the Description page of Project Settings.


#include "Gadget_Grappling.h"
#include "DrawDebugHelpers.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

void AGadget_Grappling::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("gadget grappling spawned"));
    bIsInUsage=true;
}

void AGadget_Grappling::UseGadget_Implementation()
{
    if(bIsInUsage)
    {
        bIsInUsage=false;
    FHitResult HitResult;
	FVector Location;
    FRotator Rotation;
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if(OwnerPawn->GetController() == nullptr) return;
    OwnerPawn->GetController()->GetPlayerViewPoint(Location,Rotation);
	FVector EndLocation =Location+ Rotation.Vector()*GrapplingDistance;
	FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(this);
    TraceParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult,Location,EndLocation,ECC_Visibility,TraceParams);
	if(!HitResult.ImpactPoint.IsZero())
	{
        bIsInUsage=false;
        UE_LOG(LogTemp, Display, TEXT("You have hit"));
        TargetLocation=HitResult.ImpactPoint;
        if(GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()) && GrapplingAnimation)
        {
        IINF_MainChar::Execute_InterfacePlayAnimation(GetOwner(),GrapplingAnimation,1);
        IINF_MainChar::Execute_InterfaceJump(GetOwner());
        }
        GetWorld()->GetTimerManager().SetTimer(GrapplingTimerHandle,this,&AGadget_Grappling::Grappling,GetWorld()->GetDeltaSeconds()*0.1,true);
	}
    }
    else
    {
     GetWorld()->GetTimerManager().ClearTimer(GrapplingTimerHandle);
     bIsInUsage=true;
    }
}

void AGadget_Grappling::Grappling()
{
        // Mathematic
        float DistanceToTarget = FVector::Dist(Owner->GetActorLocation(),TargetLocation);
        
        //End of grappling
        if (DistanceToTarget <= GrapRadius)
        {
            UE_LOG(LogTemp, Display, TEXT("Your grap"));
            GetWorld()->GetTimerManager().ClearTimer(GrapplingTimerHandle);
            bIsInUsage=true;

          /* new */ 
    FVector StartLocation = GetOwner()->GetActorLocation();
    FQuat Rotation = FQuat::Identity;
    FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(ClingRadius, ClingRadius);

    // Sphere line trace settings
    FCollisionQueryParams TraceParams;
    TraceParams.bTraceComplex = true;
    TraceParams.bReturnPhysicalMaterial = false;
    TraceParams.AddIgnoredActor(GetOwner());

    // Sphere line trace
    FHitResult HitResult;
    bool bHit = GetWorld()->SweepSingleByChannel(HitResult, StartLocation, StartLocation, Rotation, ECC_Visibility, CollisionShape, TraceParams);
	if(bHit && Cast<ACharacter>(GetOwner())->GetCharacterMovement()->IsFalling())
	{
		// Climbing
		UE_LOG(LogTemp, Display, TEXT("climb actor: %s"),*HitResult.GetActor()->GetActorNameOrLabel());
	Cast<ACharacter>(GetOwner())->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	DrawDebugSphere(GetWorld(),GetOwner()->GetActorLocation(),50,12,FColor::Red,false,5);
    if(GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    IINF_MainChar::Execute_SetClingingStatus(GetOwner(),bHit);
    }
        }
        else //grappling mechanic
        {
           FVector CurrentLocation = Owner->GetActorLocation();

        // Searching fo direction
        FVector PullDirection = (TargetLocation - CurrentLocation).GetSafeNormal();
        // Searchingg for new character position
        FVector NewLocation = CurrentLocation + PullDirection * GrapSpeed * GetWorld()->GetDeltaSeconds();

        // Movement
        Owner->SetActorLocation(NewLocation);
        }
}
