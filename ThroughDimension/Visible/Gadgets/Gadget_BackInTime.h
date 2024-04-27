// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GadgetMechanicBase.h"
#include "Gadget_BackInTime.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API AGadget_BackInTime : public AGadgetMechanicBase
{
	GENERATED_BODY()
	public:

	virtual void UseGadget_Implementation()override;

	virtual void CustomDestroy_Implementation() override;

	FVector SaveLocation;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* TimeParticle;
};
