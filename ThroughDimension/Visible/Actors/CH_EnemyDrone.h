// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_CheckSavedActors.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemyDrone.h"
#include "CH_EnemyDrone.generated.h"

UCLASS()
class THROUGHDIMENSION_API ACH_EnemyDrone : public ACharacter,public IINF_EnemyDrone ,public IINF_CheckSavedActors
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACH_EnemyDrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual float GetDronePatrolLength_Implementation(){return PatrolLength;};

private:
UPROPERTY(VisibleAnywhere)
class UStaticMeshComponent* DroneMesh;
UCharacterMovementComponent* CharacterMovement;
UPROPERTY(EditAnywhere)
class UParticleSystem* DeathParticle;
UPROPERTY(EditAnywhere)
float PatrolLength=1000;
};
