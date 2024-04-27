// Fill out your copyright notice in the Description page of Project Settings.


#include "CH_MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_Gun.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainController.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/Visible/Components/AC_Stamina.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/Visible/Components/AC_ItemStorage.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/MainGameStateBase.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainGameMode.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/MainSaveGame.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACH_MainCharacter::ACH_MainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
	Camera = CreateDefaultSubobject<UCameraComponent>("Main Camera");
	Camera->SetupAttachment(GetMesh());
	Camera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("Head"));


	InteractionComponent=CreateDefaultSubobject<USceneComponent>("Interaction Component");
	InteractionComponent->SetupAttachment(GetMesh());
	InteractionComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "LeftHandSocket");

	StaminaComp=CreateDefaultSubobject<UAC_Stamina>("Stamina Component");
    
	ItemStorageComp=CreateDefaultSubobject<UAC_ItemStorage>("Item Storage Component");

	Camera->bUsePawnControlRotation=true;

   //Camera settings
   bUseControllerRotationPitch=false;
   bUseControllerRotationYaw=true;
   bUseControllerRotationRoll=false;
}


/*
Getters
*/
bool ACH_MainCharacter::GetStayingStatus_Implementation()
{
    return bIsStanding;
}

bool ACH_MainCharacter::GetSlidingStatus_Implementation()
{
    return bIsSliding;
}

bool ACH_MainCharacter::GetAliveStatus_Implementation()
{
    return bIsAlive;
}

UObject *ACH_MainCharacter::GetItemStorage_Implementation()
{
    return ItemStorageComp.Get();
}

AActor *ACH_MainCharacter::GetGun_Implementation()
{
    return CurrentGun;
}

AController *ACH_MainCharacter::GetCharacterController_Implementation()
{
    return GetController();
}

void ACH_MainCharacter::InterfaceGetViewPoint_Implementation(FVector &outLocation, FRotator &outRotation)
{
	GetController()->GetPlayerViewPoint(outLocation,outRotation);
}



/*
Interface functions
*/
void ACH_MainCharacter::SetClingingStatus_Implementation(bool status)
{
  bIsClinging=status;
}

void ACH_MainCharacter::AttachToInteractComponent_Implementation(AActor* Item)
{
	Item->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "LeftHandSocket");
}

void ACH_MainCharacter::Sliding_Implementation()
{
	bIsSliding=true;
	GetCapsuleComponent()->SetCapsuleHalfHeight(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()/1.5);
	UE_LOG(LogTemp, Display, TEXT("started sliding"));
	
}

void ACH_MainCharacter::EndSliding_Implementation()
{
	bIsSliding=false;
	GetCapsuleComponent()->SetCapsuleHalfHeight(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()*1.5);
	GetMesh()->GetAnimInstance()->StopAllMontages(0);
}

void ACH_MainCharacter::InterfacePlayAnimation_Implementation(UAnimMontage *AnimMontage,float PlayRate)
{
  PlayAnimMontage(AnimMontage,PlayRate,NAME_None);
}

void ACH_MainCharacter::InterfaceStopAllMontages_Implementation()
{
	GetMesh()->GetAnimInstance()->StopAllMontages(0.1f);
}

/*
Basic function BeginPlay, Constructor etc...
*/

void ACH_MainCharacter::BeginPlay()
{
	Super::BeginPlay();
	// Spawn Weapon
	if(DefaultGunClass)
	{
		CurrentGun=GetWorld()->SpawnActor<AActor>(DefaultGunClass);
	}
	if(CurrentGun)
    {
    CurrentGun->SetOwner(this);
    CurrentGun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	UE_LOG(LogTemp, Warning, TEXT("weaponsocket"));
    }
	
}


void ACH_MainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    //Bind movement inputs
	PlayerInputComponent->BindAxis("MoveForwardBack",this,&ACH_MainCharacter::MoveForwardBack);
    PlayerInputComponent->BindAxis("MoveRightLeft",this,&ACH_MainCharacter::MoveRightLeft);
	PlayerInputComponent->BindAction("CharacterJump",IE_Pressed, this, &ACH_MainCharacter::CharacterJump);
	//PlayerInputComponent->BindAction("Squat",IE_Pressed, this, &ACH_MainCharacter::Squat);
	PlayerInputComponent->BindAction("Sliding",IE_Pressed, this, &ACH_MainCharacter::StartSliding);
	PlayerInputComponent->BindAction("Strafe",IE_Pressed, this, &ACH_MainCharacter::Strafe);
	//Bind camera inputs
	PlayerInputComponent->BindAxis("TurnUpDown", this, &ACH_MainCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRightLeft", this, &ACH_MainCharacter::AddControllerYawInput);
    //Bind interact inputs
	PlayerInputComponent->BindAction("Shoot",IE_Pressed, this, &ACH_MainCharacter::CharacterShoot);
	PlayerInputComponent->BindAction("Climb",IE_Pressed, this, &ACH_MainCharacter::Climb);
	PlayerInputComponent->BindAction("SlowMo",IE_Pressed, this, &ACH_MainCharacter::SlowMo);
	PlayerInputComponent->BindAction("ShowGadgets",IE_Pressed, this, &ACH_MainCharacter::ShowGadgets);
	PlayerInputComponent->BindAction("UseExtraGadget",IE_Pressed, this, &ACH_MainCharacter::UseExtraGadget);
	PlayerInputComponent->BindAction("Reload",IE_Pressed, this, &ACH_MainCharacter::ReloadWeapon);
	//PlayerInputComponent->BindAction("SaveGame",IE_Pressed, this, &ACH_MainCharacter::SaveTheGame);
	//PlayerInputComponent->BindAction("LoadGame",IE_Pressed, this, &ACH_MainCharacter::LoadTheGame);
	PlayerInputComponent->BindAxis("ChooseGadget",this,&ACH_MainCharacter::ChooseGadget);
	PlayerInputComponent->BindAction("OpenMenu",IE_Pressed,this,&ACH_MainCharacter::OpenMenu);
}


/*
Movement functions
*/
void ACH_MainCharacter::MoveForwardBack(float value)
{
	if(Controller && !bIsClinging)
	{
		AddMovementInput(GetActorForwardVector(),value);
	}
}

void ACH_MainCharacter::MoveRightLeft(float value)
{
	if(Controller && !bIsClinging)
	{
		AddMovementInput(GetActorRightVector(),value);
	}
}

void ACH_MainCharacter::CharacterJump()
{
	if (Controller && !GetCharacterMovement()->IsFalling()&& !bIsClinging && !bIsSliding)
	{
		Jump();
	}
	else if(bIsSliding)
	{
	 InterfaceStopAllMontages_Implementation();
	 Jump();
	 GetCapsuleComponent()->SetCapsuleHalfHeight(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()*1.5);
	 bIsSliding=false;
	}
	else if(bIsClinging)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		LaunchCharacter(GetActorForwardVector()*StrafeStrength,true,true);
		bIsClinging=false;
	}
}

void ACH_MainCharacter::Squat()
{
	bIsStanding=!bIsStanding;
	if(!bIsStanding)
	{
     UE_LOG(LogTemp, Warning, TEXT("You are squatting"));
	 GetCapsuleComponent()->SetCapsuleHalfHeight(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()/1.5);
	 GetCharacterMovement()->MaxWalkSpeed=GetCharacterMovement()->MaxWalkSpeed/1.5;
	}
	else
	{
     UE_LOG(LogTemp, Warning, TEXT("You are not squatting"));
	 // Stand LineTrace
     FHitResult HitRes;
	 FVector Location=GetActorLocation();
	 FVector EndLocation = Location+FVector(0.0f, 0.0f,GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()*1.5+10);
	 FCollisionQueryParams TraceParams;
	 TraceParams.AddIgnoredActor(this);
	 GetWorld()->LineTraceSingleByChannel(HitRes,Location,EndLocation,ECC_Visibility,TraceParams);
	 //Capsule Size change
	 if(!HitRes.GetActor())
	 {
	 GetCapsuleComponent()->SetCapsuleHalfHeight(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()*1.5);
	 GetCharacterMovement()->MaxWalkSpeed=GetCharacterMovement()->MaxWalkSpeed*1.5;
	 }
	 else
	 {
	  bIsStanding=!bIsStanding;
	 }
	}
}

void ACH_MainCharacter::StartSliding()
{
	if(GetCharacterMovement()->IsFalling()||GetMovementComponent()->GetLastInputVector().IsZero() || !SlideAnim || bIsSliding || bIsUsingGadget || !bIsStanding) return;
	UE_LOG(LogTemp, Warning, TEXT("you slide"));
	// Start sliding system
	PlayAnimMontage(SlideAnim,1.0,NAME_None);
	StartSlidingLocation=GetActorLocation();
}

void ACH_MainCharacter::Strafe()
{
	UE_LOG(LogTemp, Warning, TEXT("you strafe"));
	if(!(ItemStorageComp->Stamina >= ItemStorageComp->StrafeCost) || bIsUsingGadget || !bIsStanding) return;
	if(StrafeSound)
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), StrafeSound,GetActorLocation());

	if(GetMovementComponent()->IsFalling())
	{
	LaunchCharacter(GetMovementComponent()->GetLastInputVector()*StrafeStrength,true,true);
	}
	else
	{
    LaunchCharacter(GetMovementComponent()->GetLastInputVector()*(StrafeStrength*2),true,true);
	}
	ItemStorageComp->StaminaUse(ItemStorageComp->StrafeCost);
}

void ACH_MainCharacter::Climb()
{
	Cast<AMainGameStateBase>(GetWorld()->GetGameState())->CheckDestroyedPawns();
	UMainSaveGame* LoadedGame = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot", 0));
	UE_LOG(LogTemp, Display, TEXT("saved location %s"),*LoadedGame->PlayerLocation.ToString());
}


/*
Gameplay mechanic functions
*/
void ACH_MainCharacter::UseExtraGadget()
{
	if(ItemStorageComp && !bIsSliding)
	{
		ItemStorageComp->UseExtraGadget();
	}
}

void ACH_MainCharacter::ReloadWeapon()
{
	if(!CurrentGun|| bIsUsingGadget) return;
	IINF_Gun::Execute_Reload(CurrentGun);
}

float ACH_MainCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{ 
	if(DeathParticle)
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),DeathParticle,GetActorLocation());

	if(UGameplayStatics::GetGameMode(GetWorld())->GetClass()->ImplementsInterface(UINF_MainGameMode::StaticClass()))
	IINF_MainGameMode::Execute_EndGame(UGameplayStatics::GetGameMode(GetWorld()));
	bIsAlive=false;
	Destroy();
    return 0.0f;
}

void ACH_MainCharacter::SlowMo()
{
	if(ItemStorageComp.Get()->SlowMoCharge<=0) return;
    
	ItemStorageComp.Get()->SlowMoUsed();
	if(StrafeSound)
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), StrafeSound,GetActorLocation());
}

void ACH_MainCharacter::ShowGadgets()
{
	if(ItemStorageComp && !ItemStorageComp->bInventoryIsOpen)
	{
		UE_LOG(LogTemp, Display, TEXT("opening inventory"));
     ItemStorageComp->OpenInventory();
	}
	else if(ItemStorageComp->bInventoryIsOpen)
	{
		UE_LOG(LogTemp, Display, TEXT("closing inventory"));
	 ItemStorageComp->CloseInventory();
	}
}

void ACH_MainCharacter::ChooseGadget(float number)
{
	if(!ItemStorageComp->bInventoryIsOpen || number==0) return;
	if(number>ItemStorageComp->GadgetsArray.Max()) number=ItemStorageComp->GadgetsArray.Max()-1;
	if(number<=0)number=1;
	ItemStorageComp->ChooseGadgetWithKey(number-1);
}

void ACH_MainCharacter::SaveTheGame()
{
	if(Cast<IINF_MainGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
     IINF_MainGameMode::Execute_SaveGame(UGameplayStatics::GetGameMode(GetWorld()));
	}
}

void ACH_MainCharacter::LoadTheGame()
{
	if(Cast<IINF_MainGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
     IINF_MainGameMode::Execute_ReloadGame(UGameplayStatics::GetGameMode(GetWorld()),true);
	}
}

void ACH_MainCharacter::OpenMenu()
{
 if(GetController()->GetClass()->ImplementsInterface(UINF_MainController::StaticClass()))
 {
	IINF_MainController::Execute_OpenMenu(GetController());
 }
}

void ACH_MainCharacter::CharacterShoot()
{
	if(!CurrentGun|| bIsUsingGadget) return;
	IINF_Gun::Execute_Shoot(CurrentGun);
}
