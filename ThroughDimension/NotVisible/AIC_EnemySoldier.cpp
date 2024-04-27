// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_EnemySoldier.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Prediction.h"
#include "Perception/AISense_Prediction.h"
#include "Perception/AISenseConfig_Team.h"
#include "Perception/AISense_Team.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_EnemySoldier.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

/*
Basic Functions
*/
AAIC_EnemySoldier::AAIC_EnemySoldier()
{
    SetupPerceptionSystem();
}

void AAIC_EnemySoldier::BeginPlay()
{
    Super::BeginPlay();
    if(AIBehaviorTree!=nullptr)
    {
        RunBehaviorTree(AIBehaviorTree);
    }
    AIPerceptions->OnTargetPerceptionUpdated.AddDynamic(this,&AAIC_EnemySoldier::OnSight);
    if(GetPawn()&& GetPawn()->GetClass()&&GetPawn()->GetClass()->ImplementsInterface(UINF_EnemySoldier::StaticClass()))
    {
        ShootRange=IINF_EnemySoldier::Execute_GetSoldierShootRange(GetPawn());
    }
}

void AAIC_EnemySoldier::SetupPerceptionSystem()
{
  SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component"));
  AIPerceptions=GetPerceptionComponent();
  SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
  PredictionConfig = CreateDefaultSubobject<UAISenseConfig_Prediction>("Prediction Config");
  TeamConfig=CreateDefaultSubobject<UAISenseConfig_Team>("Team Config");
  SightConfig->SetMaxAge(0.0f);
  AIPerceptions->ConfigureSense(*SightConfig);
  AIPerceptions->ConfigureSense(*PredictionConfig);
  AIPerceptions->ConfigureSense(*TeamConfig);
  AIPerceptions->SetDominantSense(SightConfig->GetSenseImplementation());
  SetGenericTeamId(FGenericTeamId(1));
}

/*
Perception functions
*/

void AAIC_EnemySoldier::OnSight(AActor* Actor, FAIStimulus Stimulus)
{
    if (!Actor->ActorHasTag("Player")|| !GetPawn()||!Actor) return;
    
    if(!LineOfSightTo(Actor))//If lost target from the sight line
    {
        UE_LOG(LogTemp, Display, TEXT("not on line"));
     GetBlackboardComponent()->SetValueAsVector("PlayerLocationForMove",Actor->GetActorLocation());
     GetWorldTimerManager().ClearTimer(Shooting);
     bIsShooting=false;
    }
    else
    {
     //Team communication
     TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel3));
    TArray<AActor*> ActorsInRadius;
    UKismetSystemLibrary::SphereOverlapActors(GetWorld(),GetPawn()->GetActorLocation(),1200,ObjectTypes,nullptr,{},ActorsInRadius);
    for(auto TeamMate:ActorsInRadius)
    {
        if(TeamMate->GetInstigatorController()==GetPawn()->GetInstigatorController()) continue;
        if(TeamMate->GetInstigatorController()->GetClass()->ImplementsInterface(UINF_EnemyAiController::StaticClass()))
        {
            IINF_EnemyAiController::Execute_SetTargetLocation(TeamMate->GetInstigatorController(),Actor->GetActorLocation());
        }
    }
     //Common Ai settings   
     float Distance = FVector::Distance(Actor->GetActorLocation(),GetPawn()->GetActorLocation());
     //Request prediction and focus
     if(!bLookingAtDecoy)
     UAISense_Prediction::RequestControllerPredictionEvent(this,Actor,0.1);
     SetFocus(Actor);
     GetBlackboardComponent()->SetValueAsVector("PlayerLocationForFocus",Actor->GetActorLocation());
     FVector MoveLocation = Actor->GetActorLocation()+(GetPawn()->GetActorLocation()-Actor->GetActorLocation()).GetSafeNormal()*(ShootRange-50);
     UE_LOG(LogTemp, Display, TEXT("pre if"));
     // Situation check
     if (!bHasTarget&& Distance>ShootRange) //Situation if AI does not have a target and not in the Shoot Range
        { 
            UE_LOG(LogTemp, Display, TEXT("if"));
            bHasTarget=false;
            TargetAimRotation=FRotator();
            //Allow movement to target
            GetBlackboardComponent()->SetValueAsVector("PlayerLocationForMove",MoveLocation);
        }
        else if(bHasTarget && Distance>ShootRange+400)//Situation if have a target but losing the Shoot Range capacity
        {
            UE_LOG(LogTemp, Display, TEXT("else if"));
            bHasTarget=false;
            bIsShooting=false;
            TargetAimRotation=FRotator();
            //Allow movement to target
            GetBlackboardComponent()->SetValueAsVector("PlayerLocationForMove",MoveLocation);
        }
     else // Have a target and in the shoot range
        {
        StopMovement();
        UE_LOG(LogTemp, Display, TEXT("bIsShooting= %d"),bIsShooting);
        if(bIsShooting) return;
        //Statuses
        bIsShooting=true;
        bHasTarget=true;
        
        //Aim rotation setings
        FRotator NewControlRotation = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), Actor->GetActorLocation());
        SetControlRotation(NewControlRotation);
        TargetAimRotation=NewControlRotation;
        
        //Shooting
        // DrawDebugLine(GetWorld(),GetPawn()->GetActorLocation(),GetPawn()->GetActorLocation()+GetControlRotation().Vector()*1000,FColor::Green,false,1);
        if(GetWorld())
        GetWorldTimerManager().SetTimer(Shooting,this,&AAIC_EnemySoldier::ShootingTimer,PreShootDelay,false);
        }

    
 }
}


void AAIC_EnemySoldier::OnPerceptionUpdated(const TArray<AActor *> &UpdatedActors)
{
}

void AAIC_EnemySoldier::ShootingTimer()
{
    if(!this&&!GetPawn()&& !bHasTarget) return;
    
    if(Cast<IINF_EnemySoldier>(GetPawn()))
        {
            IINF_EnemySoldier::Execute_EnemyShoot(GetPawn());
            bIsShooting=false;
        }
}

/*
Interface functions
*/
FRotator AAIC_EnemySoldier::GetAiControlRotation_Implementation()
{
    return TargetAimRotation;
}
void AAIC_EnemySoldier::AiCustomDestroy_Implementation()
{
 if(AIPerceptions)
 {
    AIPerceptions->Deactivate();
    StopMovement();
    UnPossess();

 }
 Destroy();
}

void AAIC_EnemySoldier::SetTargetLocation_Implementation(FVector Location)
{
    UE_LOG(LogTemp, Display, TEXT("targetlocation"));
    GetBlackboardComponent()->SetValueAsVector("PlayerLocationForMove",Location);
}
