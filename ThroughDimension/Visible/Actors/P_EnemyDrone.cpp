// Fill out your copyright notice in the Description page of Project Settings.


#include "P_EnemyDrone.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AP_EnemyDrone::AP_EnemyDrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Capsule=CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
	Capsule->SetupAttachment(RootComponent);
	DroneMesh=CreateDefaultSubobject<UStaticMeshComponent>("Drone Mesh");
	DroneMesh->SetupAttachment(Capsule);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

// Called when the game starts or when spawned
void AP_EnemyDrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP_EnemyDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AP_EnemyDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

