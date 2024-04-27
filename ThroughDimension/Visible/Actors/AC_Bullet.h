// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AC_Bullet.generated.h"

UCLASS()
class THROUGHDIMENSION_API AAC_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAC_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


UPROPERTY(EditAnywhere)
class UStaticMeshComponent* BulletMesh;
UPROPERTY(VisibleAnywhere)
class UProjectileMovementComponent* ProjectileMovement;
};
