// Fill out your copyright notice in the Description page of Project Settings.


#include "CH_EnemyDrone.h"
#include "Components/StaticMeshComponent.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/MainGameStateBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACH_EnemyDrone::ACH_EnemyDrone()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
	DroneMesh=CreateDefaultSubobject<UStaticMeshComponent>("Drone Mesh");
	DroneMesh->SetupAttachment(GetMesh());

	CharacterMovement = GetCharacterMovement();
}

// Called when the game starts or when spawned
void ACH_EnemyDrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACH_EnemyDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACH_EnemyDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACH_EnemyDrone::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	if(IsValid(this)&&IsValidLowLevel())
	{
		if(DeathParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),DeathParticle,GetActorLocation());
		Cast<AMainGameStateBase>(GetWorld()->GetGameState())->AddDestroyedPawn(GetActorNameOrLabel());
		Destroy();
	}
    return 0.0f;
}
