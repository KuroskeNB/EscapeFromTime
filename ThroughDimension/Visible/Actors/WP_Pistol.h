// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_Gun.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_CheckSavedActors.h"
#include "WP_Pistol.generated.h"

UCLASS()
class THROUGHDIMENSION_API AWP_Pistol : public AActor, public IINF_Gun, public IINF_CheckSavedActors
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWP_Pistol();

    /*
	Interface functions
	*/
	UFUNCTION(BlueprintNativeEvent)
    void Shoot();
    virtual void Shoot_Implementation() override;
	UFUNCTION(BlueprintNativeEvent)
    float GetMaxAmmoCount();
	virtual float GetMaxAmmoCount_Implementation();
    UFUNCTION(BlueprintNativeEvent)
	float GetCurrentAmmoCount();
    virtual float GetCurrentAmmoCount_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    void FinishReload();
	virtual void FinishReload_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    void Reload();
	virtual void Reload_Implementation();

	virtual void SetShootingDelay_Implementation(float Delay){ShootingDelay=Delay;};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


private:
/*
Private properties
*/
UPROPERTY(EditAnywhere)
TObjectPtr<class USkeletalMeshComponent> GunMesh;
UPROPERTY(EditAnywhere)
TObjectPtr<class USceneComponent> BarrelComponent;
UPROPERTY(EditAnywhere)
float Damage =1;
UPROPERTY(EditAnywhere)
float MaxAmmo=12;
float CurrentAmmo;
UPROPERTY(EditAnywhere)
class USoundBase* ShootSound;

bool bIsReloading =false;

bool bCanShoot=true;
UPROPERTY(EditAnywhere)
float ShootingDelay =1;
UPROPERTY(EditAnywhere, Category = "TraceSettings")
TEnumAsByte<ECollisionChannel> TraceChannel;
UPROPERTY(EditAnywhere)
TSubclassOf<AActor> BulletClass;
UPROPERTY(EditAnywhere)
TSoftObjectPtr<class USoundBase> HitSound;
UPROPERTY(EditAnywhere)
class UParticleSystem* ShootParticle; // Without TPtr because of optimization reasons
UPROPERTY(EditAnywhere)
class UAnimMontage* ShootAnim;
UPROPERTY(EditAnywhere)
class UAnimMontage* ReloadAnim;
/*
Private functions
*/

  
};
