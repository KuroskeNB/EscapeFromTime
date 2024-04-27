// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GadgetMechanicBase.h"
#include "Gadget_Shield.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API AGadget_Shield : public AGadgetMechanicBase
{
	GENERATED_BODY()
	public:

	virtual void UseGadget_Implementation()override;

	virtual void CustomDestroy_Implementation() override;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ShieldAnimation;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ShieldClass;
	class AActor* Shield;

	virtual bool GetInUsageStatus_Implementation() override;
};
