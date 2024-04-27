// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Stamina.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THROUGHDIMENSION_API UAC_Stamina : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Stamina();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float Stamina = 100;
	UPROPERTY(EditAnywhere)
	float StrafeCost = 25;
    UFUNCTION()
	void StaminaUse(float Cost);
	UFUNCTION()
	void StaminaRestore();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
//UPROPERTY(EditAnywhere)
//TSubclassOf<class UUserWidget> StaminaWidgetClass;
//class UUserWidget* StaminaWidget;

struct FTimerHandle StaminaRestoreTimer;
struct FTimerHandle RestoreTimer;


};
