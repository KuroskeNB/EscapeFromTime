// Fill out your copyright notice in the Description page of Project Settings.


#include "Mesh_Shield.h"

// Sets default values
AMesh_Shield::AMesh_Shield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMesh_Shield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMesh_Shield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

