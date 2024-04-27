// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_EnemyDrone.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API AAIC_EnemyDrone : public AAIController
{
	GENERATED_BODY()
	public:
    AAIC_EnemyDrone();
    virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnSight(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void StartPatrol();

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree;

	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* AIPerceptions;

	class UAISenseConfig_Sight* SightConfig;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAC_EnemySpawn> SpawnerClass;

	struct FTimerHandle EnemySpawnCD;
	bool bCanSpawn=true;
	UPROPERTY(EditAnywhere)
	float SpawnCD=60;
	UPROPERTY(EditAnywhere)
    class USoundBase* DetectSound;

	/*
	Behavior properties
	*/
    UPROPERTY(EditAnywhere)
	float PatrolLength=1000;
	UPROPERTY(EditAnywhere)
	float SpawnRadius=2500;

	FVector StartLocation;
	FVector TargetLocation;
	FVector PatrolLocation;
	bool bHasTarget =false;

};
