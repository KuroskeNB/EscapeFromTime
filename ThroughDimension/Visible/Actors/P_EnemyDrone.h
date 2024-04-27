// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "P_EnemyDrone.generated.h"

UCLASS()
class THROUGHDIMENSION_API AP_EnemyDrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AP_EnemyDrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
UPROPERTY(EditAnywhere)
class UStaticMeshComponent* DroneMesh;
UPROPERTY(EditAnywhere)
class UCapsuleComponent* Capsule;
UPROPERTY(VisibleAnywhere)
class UFloatingPawnMovement* MovementComponent;
};
