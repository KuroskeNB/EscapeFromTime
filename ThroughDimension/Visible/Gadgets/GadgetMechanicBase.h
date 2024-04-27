// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_GadgetMechanic.h"
#include "GadgetMechanicBase.generated.h"

UCLASS()
class THROUGHDIMENSION_API AGadgetMechanicBase : public AActor, public IINF_GadgetMechanic
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGadgetMechanicBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	
	*/
    UFUNCTION(BlueprintNativeEvent)
    void UseGadget();
	virtual void UseGadget_Implementation()override;
	UFUNCTION(BlueprintNativeEvent)
    void CustomDestroy();
	virtual void CustomDestroy_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    bool GetInUsageStatus();
	virtual bool GetInUsageStatus_Implementation();

	bool bIsInUsage =false;

};
