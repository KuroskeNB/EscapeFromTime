// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GadgetMechanicBase.h"
#include "Gadget_Grappling.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API AGadget_Grappling : public AGadgetMechanicBase
{
	GENERATED_BODY()
	public:
	virtual void BeginPlay() override;

	virtual void UseGadget_Implementation()override;
	void Grappling();

	/*
	Properties
	*/
    UPROPERTY(EditAnywhere)
	float GrapplingDistance =1500;
	UPROPERTY(EditAnywhere)
	float GrapRadius =30;
	UPROPERTY(EditAnywhere)
	float GrapSpeed =500;
	UPROPERTY(EditAnywhere)
	float ClingRadius =30;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* GrapplingAnimation;

	struct FTimerHandle GrapplingTimerHandle;
	FVector TargetLocation;
};
