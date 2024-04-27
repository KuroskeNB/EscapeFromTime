// Fill out your copyright notice in the Description page of Project Settings.


#include "WP_Pistol.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemySoldier.h"
#include "TimerManager.h"

// Sets default values
AWP_Pistol::AWP_Pistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GunMesh=CreateDefaultSubobject<USkeletalMeshComponent>("Gun Mesh");
	GunMesh->SetupAttachment(RootComponent);

	BarrelComponent = CreateDefaultSubobject<USceneComponent>("Barrel Component");
	BarrelComponent->SetupAttachment(GunMesh.Get());

}

// Called when the game starts or when spawned
void AWP_Pistol::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo=MaxAmmo;
}

// Called every frame
void AWP_Pistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWP_Pistol::Reload_Implementation()
{   
	if(!ReloadAnim || CurrentAmmo==MaxAmmo) return;
    
	bIsReloading = true;
	if(GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
	{
	IINF_MainChar::Execute_InterfacePlayAnimation(GetOwner(),ReloadAnim,1);
	}
	if(GetOwner()->GetClass()->ImplementsInterface(UINF_EnemySoldier::StaticClass()))
	{
	IINF_EnemySoldier::Execute_InterfacePlayAnimation(GetOwner(),ReloadAnim,1);
	}
}

void AWP_Pistol::Shoot_Implementation()
{
	if(!bCanShoot ||bIsReloading) return;
	
	//Reload from shoot trying
	if(CurrentAmmo<=0)
	{
	Reload_Implementation();
	return;
	}
    
	//For not to spam shoot
	bCanShoot=false;

	//Visual
	if(ShootParticle)
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ShootParticle,BarrelComponent->GetComponentLocation());
	if(ShootAnim)
	{
		if(ShootSound)
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound,GetActorLocation());
	 if(GetOwner()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
	 {
	  IINF_MainChar::Execute_InterfacePlayAnimation(GetOwner(),ShootAnim,1);
	 }
	 if(GetOwner()->GetClass()->ImplementsInterface(UINF_EnemySoldier::StaticClass()))
	 {
	  IINF_EnemySoldier::Execute_InterfacePlayAnimation(GetOwner(),ShootAnim,1);
	 }
	}
    
	//Shoot system
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	FVector Location;
    FRotator Rotation;
	if(OwnerPawn && OwnerPawn->GetController())
	OwnerPawn->GetController()->GetPlayerViewPoint(Location,Rotation);
	FVector ShootLocation = Location+Rotation.Vector()*50;
	AActor* TempBullet =GetWorld()->SpawnActor<AActor>(BulletClass,ShootLocation,Rotation);
	TempBullet->SetOwner(GetOwner());
	UE_LOG(LogTemp, Display, TEXT("bullet owner is %s"),*TempBullet->GetOwner()->GetActorNameOrLabel());
	CurrentAmmo--;
	//Delay between shoots
	FTimerHandle ShootDelay;
	GetWorldTimerManager().SetTimer(ShootDelay,[this](){bCanShoot=true;},ShootingDelay,false);
}

float AWP_Pistol::GetMaxAmmoCount_Implementation()
{
    return MaxAmmo;
}

float AWP_Pistol::GetCurrentAmmoCount_Implementation()
{
    return CurrentAmmo;
}

void AWP_Pistol::FinishReload_Implementation()
{
 CurrentAmmo=MaxAmmo;
 bIsReloading=false;
}