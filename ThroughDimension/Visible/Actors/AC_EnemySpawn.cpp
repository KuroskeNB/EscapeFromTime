// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_EnemySpawn.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemyAiController.h"

// Sets default values
AAC_EnemySpawn::AAC_EnemySpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAC_EnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAC_EnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAC_EnemySpawn::SpawnThemAll(FVector TargetLocation)
{
	UE_LOG(LogTemp, Display, TEXT("spawn them all"));
	FVector Origin = GetActorLocation();

            FNavLocation RandomLocation;
            UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
            if (NavSystem )
            {
				for(int32 i =0;i<SpawnCount;i++)
				{
					//NewEnemy spawn settings
					FActorSpawnParameters SpawnParameters;
					SpawnParameters.bDeferConstruction=SpawnableAiController!=nullptr;
					SpawnParameters.ObjectFlags|=RF_Transient;
				NavSystem->GetRandomReachablePointInRadius(Origin, SpawnRadius, RandomLocation);
				//Spawning
				APawn* SpawnedCharacter=GetWorld()->SpawnActor<APawn>(SpawnableCharacter,RandomLocation.Location,FRotator(),SpawnParameters);
				SpawnedCharacter->FinishSpawning(FTransform(FRotator(),RandomLocation,GetActorScale3D()));
				SpawnedCharacter->AIControllerClass=SpawnableAiController;
				SpawnedCharacter->SpawnDefaultController();
				SpawnedCharacter->Tags.Add("DroneSpawned");
				if(SpawnedCharacter->GetController())
				IINF_EnemyAiController::Execute_SetTargetLocation(SpawnedCharacter->GetController(),TargetLocation);
				Destroy();
				}
                
            }
}
