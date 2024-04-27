// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_ClingComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UAC_ClingComponent::UAC_ClingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAC_ClingComponent::TryWallCling()
{
	UE_LOG(LogTemp, Display, TEXT("trying to climb"));
	if(!bIsClimbing)
	{
		// properties for climbing check
		UE_LOG(LogTemp, Display, TEXT(" in trying to climb"));
	FVector StartLocation = GetOwner()->GetActorLocation();
    float Radius = ClimbRadius; 
    float HalfHeight = ClimbRadiusHeight;
    FQuat Rotation = FQuat::Identity;
    FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(Radius, HalfHeight);

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
	bIsClimbing=true;
	Cast<ACharacter>(GetOwner())->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	DrawDebugSphere(GetWorld(),GetComponentLocation(),ClimbRadius,12,FColor::Red,false,5);
	}
	}
	else
	{
	Cast<ACharacter>(GetOwner())->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	bIsClimbing=false;
	}
}

// Called when the game starts
void UAC_ClingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_ClingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

