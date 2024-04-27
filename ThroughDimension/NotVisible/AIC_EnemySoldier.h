// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemyAiController.h"
#include "AIC_EnemySoldier.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API AAIC_EnemySoldier : public AAIController, public IINF_EnemyAiController
{
	GENERATED_BODY()
	public:
    UPROPERTY(VisibleAnywhere)
	FRotator TargetAimRotation=FRotator();

    AAIC_EnemySoldier();
	virtual void BeginPlay() override;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnSight(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void ShootingTimer();

    UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree;

	UPROPERTY(VisibleAnywhere)
	class UAIPerceptionComponent* AIPerceptions;

    
	class UAISenseConfig_Prediction* PredictionConfig;
	class UAISenseConfig_Sight* SightConfig;
	class UAISenseConfig_Team* TeamConfig;

	UPROPERTY()
	bool bHasTarget =false;
	UPROPERTY(EditAnywhere)
    float ShootRange=800;
	UPROPERTY(EditAnywhere)
	float PreShootDelay=1;
	bool bIsShooting=false;

	bool bLookingAtDecoy=false;
    
	 UPROPERTY()
	struct FTimerHandle Shooting;
	/*
	Interface functions
	*/
    UFUNCTION(BlueprintNativeEvent)
    FORCEINLINE bool GetHasTarget();
	FORCEINLINE virtual bool GetHasTarget_Implementation(){return bHasTarget;};
	UFUNCTION(BlueprintNativeEvent)
    FRotator GetAiControlRotation();
	virtual FRotator GetAiControlRotation_Implementation() override;
	UFUNCTION(BlueprintNativeEvent)
	FORCEINLINE float GetAiControlPitchRotation();
    FORCEINLINE float GetAiControlPitchRotation_Implementation(){return GetControlRotation().Pitch;};
	UFUNCTION(BlueprintNativeEvent)
    void AiCustomDestroy();
	virtual void AiCustomDestroy_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    void SetTargetLocation(FVector Location);
	virtual void SetTargetLocation_Implementation(FVector Location);

};
