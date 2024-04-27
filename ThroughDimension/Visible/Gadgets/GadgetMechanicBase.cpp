// Fill out your copyright notice in the Description page of Project Settings.


#include "GadgetMechanicBase.h"

// Sets default values
AGadgetMechanicBase::AGadgetMechanicBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGadgetMechanicBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGadgetMechanicBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGadgetMechanicBase::UseGadget_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("You used gadget"));
}

void AGadgetMechanicBase::CustomDestroy_Implementation()
{
	Destroy();
}

bool AGadgetMechanicBase::GetInUsageStatus_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("get in uage status %d"),bIsInUsage);
	return bIsInUsage;
}
