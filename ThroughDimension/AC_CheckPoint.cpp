// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_CheckPoint.h"
#include "Components/BoxComponent.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"

// Sets default values
AAC_CheckPoint::AAC_CheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
        RootComponent = BoxCollision;
}

void AAC_CheckPoint::SaveTheGame(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<IINF_MainGameMode>(UGameplayStatics::GetGameMode(GetWorld())) &&OtherActor->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("save game"));
     IINF_MainGameMode::Execute_SaveGame(UGameplayStatics::GetGameMode(GetWorld()));
	 Destroy();
	}
}

// Called when the game starts or when spawned
void AAC_CheckPoint::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this,&AAC_CheckPoint::SaveTheGame);
}

// Called every frame
void AAC_CheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

