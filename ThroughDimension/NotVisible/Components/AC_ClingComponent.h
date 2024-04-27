// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AC_ClingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THROUGHDIMENSION_API UAC_ClingComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_ClingComponent();

	// Cling system functions
	void TryWallCling();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//status
	bool bIsClimbing=false;

private:
UPROPERTY(EditAnywhere)
float ClimbRadius = 25;
UPROPERTY(EditAnywhere)
float ClimbRadiusHeight=10;

		
};
