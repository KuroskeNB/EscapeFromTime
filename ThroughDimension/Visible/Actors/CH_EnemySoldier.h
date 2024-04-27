// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemySoldier.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_CheckSavedActors.h"
#include "CH_EnemySoldier.generated.h"

UCLASS()
class THROUGHDIMENSION_API ACH_EnemySoldier : public ACharacter, public IINF_EnemySoldier, public IINF_CheckSavedActors
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACH_EnemySoldier();

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

	UFUNCTION(BlueprintNativeEvent)
    FORCEINLINE AActor* GetGun();
    FORCEINLINE virtual AActor* GetGun_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    void EnemyShoot();
	virtual void EnemyShoot_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    void InterfacePlayAnimation(class UAnimMontage* AnimMontage,float PlayRate);
	virtual void InterfacePlayAnimation_Implementation(class UAnimMontage* AnimMontage,float PlayRate) override;

	bool bSpawnWeapon=true;
	UFUNCTION(BlueprintNativeEvent)
    void SetSpawnWeapon(bool ShouldSpawn);
	virtual void SetSpawnWeapon_Implementation(bool ShouldSpawn){bSpawnWeapon=ShouldSpawn;};
	private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf <class AActor>DefaultGunClass;
	class AActor* CurrentGun;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere)
	float ShootRange =1400;
    UPROPERTY(EditAnywhere)
	float ShootingDelay=0.8;
	virtual float GetSoldierShootRange_Implementation(){return ShootRange;};
	
	

};
