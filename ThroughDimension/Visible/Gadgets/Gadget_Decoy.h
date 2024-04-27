// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GadgetMechanicBase.h"
#include "Gadget_Decoy.generated.h"

/**
 * 
 */
UCLASS()
class THROUGHDIMENSION_API AGadget_Decoy : public AGadgetMechanicBase
{
	GENERATED_BODY()
	public:
	virtual void UseGadget_Implementation()override;

	private:
	UPROPERTY(EditAnywhere)
    TSubclassOf<AActor> DecoyActorClass;
};
