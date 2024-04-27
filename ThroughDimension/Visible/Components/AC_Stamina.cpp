// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_Stamina.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UAC_Stamina::UAC_Stamina()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_Stamina::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_Stamina::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_Stamina::StaminaUse(float Cost)
{
	Stamina-=Cost;
	GetWorld()->GetTimerManager().SetTimer(StaminaRestoreTimer,this,&UAC_Stamina::StaminaRestore,3,false);
}

void UAC_Stamina::StaminaRestore()
{
	GetWorld()->GetTimerManager().SetTimer(RestoreTimer,[this]()
	{
	if(Stamina<100)
	 {
      Stamina+=10;
	 }
	 if(Stamina>=100)
	 {
	 Stamina=100;
	 GetWorld()->GetTimerManager().ClearTimer(RestoreTimer);
	 }
	},0.5,true);
}
