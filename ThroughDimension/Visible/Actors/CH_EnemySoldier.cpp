// Fill out your copyright notice in the Description page of Project Settings.


#include "CH_EnemySoldier.h"
#include "Kismet/GameplayStatics.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_Gun.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemyAiController.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/MainGameStateBase.h"

// Sets default values
ACH_EnemySoldier::ACH_EnemySoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACH_EnemySoldier::BeginPlay()
{
	Super::BeginPlay();
	if(DefaultGunClass && bSpawnWeapon)
	{
		CurrentGun=GetWorld()->SpawnActor<AActor>(DefaultGunClass);
	}
	if(CurrentGun)
    {
    CurrentGun->SetOwner(this);
    CurrentGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	UE_LOG(LogTemp, Warning, TEXT("weaponsocket"));
	if(CurrentGun->GetClass()->ImplementsInterface(UINF_Gun::StaticClass()))
	IINF_Gun::Execute_SetShootingDelay(CurrentGun,ShootingDelay);
    }
	
}

// Called every frame
void ACH_EnemySoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACH_EnemySoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACH_EnemySoldier::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{   
	Cast<AMainGameStateBase>(GetWorld()->GetGameState())->AddDestroyedPawn(GetActorNameOrLabel());
	if(CurrentGun)
	{
		if(!ActorHasTag("DroneSpawned"))
	Cast<AMainGameStateBase>(GetWorld()->GetGameState())->AddDestroyedPawn(CurrentGun->GetActorNameOrLabel());
	CurrentGun->Destroy();
	}
	if(Controller->GetClass()->ImplementsInterface(UINF_EnemyAiController::StaticClass()))
	{
		if(DeathParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),DeathParticle,GetActorLocation());
		IINF_EnemyAiController::Execute_AiCustomDestroy(Controller);
	}
	if(IsValid(this)&&IsValidLowLevel())
	{
		Destroy();
	}
    return 0.0f;
} 

AActor *ACH_EnemySoldier::GetGun_Implementation()
{
    return CurrentGun;
}

void ACH_EnemySoldier::EnemyShoot_Implementation()
{
	if(CurrentGun&&CurrentGun->GetClass()->ImplementsInterface(UINF_Gun::StaticClass()))
	{
		IINF_Gun::Execute_Shoot(CurrentGun);
	}
}

void ACH_EnemySoldier::InterfacePlayAnimation_Implementation(UAnimMontage *AnimMontage, float PlayRate)
{
	PlayAnimMontage(AnimMontage,PlayRate,NAME_None);
}
