// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAC_Bullet::AAC_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
	BulletMesh=CreateDefaultSubobject<UStaticMeshComponent>("Bullet Mesh");
	BulletMesh->SetupAttachment(RootComponent);

	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
}

// Called when the game starts or when spawned
void AAC_Bullet::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->OnComponentHit.AddDynamic(this,&AAC_Bullet::OnOverlap);
}

void AAC_Bullet::OnOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor==GetOwner())
	{
		UE_LOG(LogTemp, Display, TEXT("destroyed bullet owner is %s"),*GetOwner()->GetActorNameOrLabel());
	Destroy();
	return;
	}
	UGameplayStatics::ApplyDamage(Hit.GetActor(),1,GetInstigatorController(),this,UDamageType::StaticClass());
	UE_LOG(LogTemp, Warning, TEXT("Hit %s"),*OtherActor->GetActorNameOrLabel());
	Destroy();
}

// Called every frame
void AAC_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


