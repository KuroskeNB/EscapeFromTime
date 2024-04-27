// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"
#include "CH_MainCharacter.generated.h"


UCLASS()
class THROUGHDIMENSION_API ACH_MainCharacter : public ACharacter, public IINF_MainChar
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACH_MainCharacter();

	/*
	Public properties
	*/
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf <class AActor>DefaultGunClass;
	class AActor* CurrentGun;
    
	/*
	Statuses
	*/
    UPROPERTY(BlueprintReadOnly)
    bool bIsStanding=true;
	UPROPERTY(BlueprintReadOnly)
    bool bIsSliding=false;
	UPROPERTY(BlueprintReadOnly)
    bool bIsAlive=true;
	UPROPERTY(BlueprintReadOnly)
    bool bIsUsingGadget=false;
	UPROPERTY(BlueprintReadOnly)
    bool bIsClinging=false;
    
	

	/*
	Statuses getters
	*/
    UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
    bool GetStayingStatus();
    virtual bool GetStayingStatus_Implementation() override;
    UFUNCTION(BlueprintNativeEvent)
    bool GetSlidingStatus();
	virtual bool GetSlidingStatus_Implementation() override;
	UFUNCTION(BlueprintNativeEvent)
    bool GetAliveStatus();
	virtual bool GetAliveStatus_Implementation() override;
	UFUNCTION(BlueprintNativeEvent)
    bool GetLeaningStatus();
	virtual bool GetLeaningStatus_Implementation() override {return bIsClinging;};
	/*
	Status setters
	*/
    UFUNCTION(BlueprintNativeEvent)
    void SetUsingGadget(bool bIsUsing);
    virtual void SetUsingGadget_Implementation(bool bIsUsing){bIsUsingGadget=bIsUsing;};
	UFUNCTION(BlueprintNativeEvent)
    void SetClingingStatus(bool status);
    virtual void SetClingingStatus_Implementation(bool status);
	/*
	Interface functions
	*/
	UFUNCTION(BlueprintNativeEvent)
	void Sliding();
	virtual void Sliding_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void EndSliding();
	virtual void EndSliding_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    FORCEINLINE UObject* GetItemStorage();
	FORCEINLINE virtual UObject* GetItemStorage_Implementation() override;
	UFUNCTION(BlueprintNativeEvent)
    AActor* GetGun(); 
	virtual AActor* GetGun_Implementation();
    UFUNCTION(BlueprintNativeEvent)
    FORCEINLINE AController* GetCharacterController();
	FORCEINLINE virtual AController* GetCharacterController_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    void InterfacePlayAnimation(class UAnimMontage* AnimMontage,float PlayRate);
	virtual void InterfacePlayAnimation_Implementation(class UAnimMontage* AnimMontage,float PlayRate) override;
	UFUNCTION(BlueprintNativeEvent)
    void InterfaceStopAllMontages();
	virtual void InterfaceStopAllMontages_Implementation();
	UFUNCTION(BlueprintNativeEvent)
    void InterfaceGetViewPoint(FVector& outLocation, FRotator& outRotation);
	virtual void InterfaceGetViewPoint_Implementation(FVector& outLocation, FRotator& outRotation);
	UFUNCTION(BlueprintNativeEvent)
    void InterfaceJump();
	virtual void InterfaceJump_Implementation() {CharacterJump();};
	UFUNCTION(BlueprintNativeEvent)
    void AttachToInteractComponent(AActor* Item);
	virtual void AttachToInteractComponent_Implementation(AActor* Item);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    

	//Movement functions
	void MoveForwardBack(float value);
	void MoveRightLeft(float value);
	void CharacterJump();
	void Squat();
	void StartSliding();
	void Strafe();
	void Climb();
	void UseExtraGadget();
	void ReloadWeapon();

	//gameplay element functions
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SlowMo();
	void ShowGadgets();
	void ChooseGadget(float number);
	void SaveTheGame();
	void LoadTheGame();
	void OpenMenu();
	
private:	
//Basic properties
UPROPERTY(VisibleAnywhere)
TObjectPtr<class UCameraComponent> Camera;
UPROPERTY(VisibleAnywhere)
TObjectPtr<class UAC_Stamina> StaminaComp;
UPROPERTY(VisibleAnywhere)
TObjectPtr<class UAC_ItemStorage> ItemStorageComp;
UPROPERTY(VisibleAnywhere)
TObjectPtr<class USceneComponent> InteractionComponent;
/*
Private functions
*/
void CharacterShoot();
/*
Private properties
*/
UPROPERTY(EditAnywhere)
class UAnimMontage* SlideAnim;
UPROPERTY(EditAnywhere)
class UAnimMontage* ShootAnim;
UPROPERTY(EditAnywhere)
class USoundBase* StrafeSound;
UPROPERTY(EditAnywhere, Category = "Setup")
float SlideSpeed=0.05f;
UPROPERTY(EditAnywhere, Category = "Setup")
float SlideLength=700;
UPROPERTY(EditAnywhere, Category = "Setup")
float SlideStrength = 18;
UPROPERTY(EditAnywhere, Category = "Setup")
float StrafeStrength = 2000;
/*
Properties for Math
*/
FVector StartSlidingLocation;
struct FTimerHandle SlidingTimer;
/*
Visual elements
*/
UPROPERTY(EditAnywhere, Category ="Visual and Sound")
class UParticleSystem* DeathParticle;
};
