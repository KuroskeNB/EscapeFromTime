// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AC_EnemySpawn.generated.h"

UCLASS()
class THROUGHDIMENSION_API AAC_EnemySpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAC_EnemySpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnThemAll(FVector TargetLocation);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACharacter> SpawnableCharacter;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AController> SpawnableAiController;
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree;
	UPROPERTY(EditAnywhere)
	float SpawnRadius=200;
	UPROPERTY(EditAnywhere)
	float SpawnCount =4;

};
