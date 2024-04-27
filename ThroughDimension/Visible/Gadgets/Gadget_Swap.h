// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GadgetMechanicBase.h"
#include "Gadget_Swap.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API AGadget_Swap : public AGadgetMechanicBase
{
	GENERATED_BODY()
	virtual void UseGadget_Implementation()override;

	UPROPERTY(EditAnywhere)
	float SwapDistance=2000;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* SwapAnimation;
	UPROPERTY(EditAnywhere)
	class UParticleSystem* SwapParticle;
};
