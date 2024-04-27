// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mesh_Decoy.generated.h"

UCLASS()
class THROUGHDIMENSION_API AMesh_Decoy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMesh_Decoy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
UPROPERTY(EditAnywhere)
class UStaticMeshComponent* DecoyMesh;
UPROPERTY(VisibleAnywhere)
class UProjectileMovementComponent* ProjectileMovement;
};
