// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_EnemyDrone.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/Visible/Actors/AC_EnemySpawn.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemyDrone.h"
#include "NavigationSystem.h"

AAIC_EnemyDrone::AAIC_EnemyDrone()
{
    SetupPerceptionSystem();
}

void AAIC_EnemyDrone::SetupPerceptionSystem()
{
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component"));
  AIPerceptions=GetPerceptionComponent();
  SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
  SightConfig->SetMaxAge(0.0f);
  AIPerceptions->ConfigureSense(*SightConfig);
  AIPerceptions->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AAIC_EnemyDrone::BeginPlay()
{
    Super::BeginPlay();
    if(AIBehaviorTree!=nullptr)
    {
        RunBehaviorTree(AIBehaviorTree);
    }
    if(GetPawn()->GetClass()->ImplementsInterface(UINF_EnemyDrone::StaticClass()))
    {
        PatrolLength=IINF_EnemyDrone::Execute_GetDronePatrolLength(GetPawn());
    }
    StartPatrol();
    AIPerceptions->OnTargetPerceptionUpdated.AddDynamic(this,&AAIC_EnemyDrone::OnSight);

    StartLocation=GetPawn()->GetActorLocation();
}

void AAIC_EnemyDrone::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(GetPawn()&&FVector::Dist(GetPawn()->GetActorLocation(), TargetLocation)<50)
    {
        TargetLocation=(TargetLocation==StartLocation) ? PatrolLocation:StartLocation;
        GetBlackboardComponent()->SetValueAsVector("PatrolPoint",TargetLocation);
    }
}

/*
Behavior tree functions
*/
void AAIC_EnemyDrone::StartPatrol()
{
    UE_LOG(LogTemp, Display, TEXT("start patrol"));
 PatrolLocation=GetPawn()->GetActorLocation()+GetPawn()->GetActorForwardVector()*PatrolLength;
 TargetLocation=PatrolLocation;
 GetBlackboardComponent()->SetValueAsVector("PatrolPoint",TargetLocation);
}

/*
Perception functions
*/
void AAIC_EnemyDrone::OnSight(AActor *Actor, FAIStimulus Stimulus)
{
    //check
    if (!GetPawn()||!Actor) return;
    if(!Actor->ActorHasTag("Player") && !Actor->ActorHasTag("PlayersBullet")) return;
    bHasTarget=true;
    GetBlackboardComponent()->SetValueAsBool("HasTarget",bHasTarget);

    UE_LOG(LogTemp, Display, TEXT("drone sight"));
    if(Actor)
    SetFocus(Actor);

    FVector VectorToFly = FVector(Actor->GetActorLocation().X, Actor->GetActorLocation().Y,GetPawn()->GetActorLocation().Z);
    GetBlackboardComponent()->SetValueAsVector("MoveTargetVector",VectorToFly);

    if(!bCanSpawn) return;

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnerClass, FoundActors);

    AActor* ClosestActor = nullptr;
    float MinDistance = TNumericLimits<float>::Max();

    for (AActor* TempActor : FoundActors)
    {
        UE_LOG(LogTemp, Display, TEXT("name found %s"),*TempActor->GetActorNameOrLabel());
        if (TempActor)
        {
            float Distance = FVector::Dist(TempActor->GetActorLocation(), GetPawn()->GetActorLocation());

            if (Distance < MinDistance)
            {
                UE_LOG(LogTemp, Display, TEXT("closest spawner found"));
                MinDistance = Distance;
                ClosestActor = TempActor;
            }
        }
    }
    if(ClosestActor)
    UE_LOG(LogTemp, Display, TEXT("name of closest spawner %s"),*ClosestActor->GetActorNameOrLabel());
    if(Cast<AAC_EnemySpawn>(ClosestActor) && MinDistance<SpawnRadius)
    {
        UE_LOG(LogTemp, Display, TEXT("spawn them all in ai"));
        if(DetectSound)
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DetectSound,GetPawn()->GetActorLocation());
    Cast<AAC_EnemySpawn>(ClosestActor)->SpawnThemAll(GetPawn()->GetActorLocation());
    }
    
    bCanSpawn=false;
    GetWorldTimerManager().SetTimer(EnemySpawnCD,[this](){bCanSpawn=true;},SpawnCD,false);
}


