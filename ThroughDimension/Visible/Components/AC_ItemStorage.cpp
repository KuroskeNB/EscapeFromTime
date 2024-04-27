// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_ItemStorage.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/Visible/Widgets/UW_Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainController.h"
#include "C:\Users\user\Documents\Unreal Projects\ThroughDimension\Source\ThroughDimension\Visible\ItemStorageData.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/Visible/Widgets/UW_GadgetButton.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_GadgetMechanic.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/Visible/Widgets/UW_ItemStorage.h"
#include "TimerManager.h"


/*
Classic functions
*/

UAC_ItemStorage::UAC_ItemStorage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAC_ItemStorage::BeginPlay()
{
	Super::BeginPlay();
	// Event binding
	OnItemStorageUpdated.AddUObject(this,&UAC_ItemStorage::InventoryOnItemStorageUpdated);
    // SlowMo limit
	SlowMoCharge=SlowMoMaximalCharge;
	Stamina=MaxStamina;
	// UI implementating
    if(ItemStorageClass)
	{
		ItemStorageUI=CreateWidget<UUW_ItemStorage>(UGameplayStatics::GetPlayerController(GetWorld(),0),ItemStorageClass);
		if(ItemStorageUI)
		ItemStorageUI->AddToViewport();
	}
	if(InventoryClass)
	{
		InventoryUI=CreateWidget<UUW_Inventory>(UGameplayStatics::GetPlayerController(GetWorld(),0),InventoryClass);
        if(InventoryUI)
		{
         InventoryUI->AddToViewport();
		 InventoryUI->OnGadgetChoosed.AddUObject(this,&UAC_ItemStorage::OnExtraGadgetChoosed);
		}
	}
   
   //Gadget innitializing
   if(GadgetDataTable)
   {
	TArray<FName> RowNames = GadgetDataTable->GetRowNames();
    for (FName RowName : RowNames)
    {
		if(RowName.IsValid())
        NewGadget(*GadgetDataTable->FindRow<FItemStorageData>(RowName,""));
	}
   }

	
}

/*
Custom Functions
*/

void UAC_ItemStorage::SlowMoUsed()
{
	if(!GetOwner()->GetInstigatorController()->GetClass()->ImplementsInterface(UINF_MainController::StaticClass())) return;

	// SlowMo count system
	if(!bIsInSlowMo)
	{
	bIsInSlowMo=true;
	GetWorld()->GetTimerManager().ClearTimer(SlowMoCDHandle);
	IINF_MainController::Execute_InterfaceSetPause(GetOwner()->GetInstigatorController(),false);
    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.25f);
	GetWorld()->GetTimerManager().SetTimer(SlowMoCDHandle,this,&UAC_ItemStorage::SlowMo,SlowMoDelay,true);
	}
	else
	{
		bIsInSlowMo=false;
     GetWorld()->GetTimerManager().ClearTimer(SlowMoCDHandle);
	 UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	 GetWorld()->GetTimerManager().SetTimer(SlowMoCDHandle,this,&UAC_ItemStorage::SlowMoRecharge,SlowMoDelay,true);
	}
}

void UAC_ItemStorage::SlowMo()
{
	SlowMoCharge-=SlowMoMomentCost;
	if(ItemStorageUI)
	ItemStorageUI->UpdateSlowMoCharge(SlowMoCharge);
	if(SlowMoCharge<=0)
	{
		bIsInSlowMo=false;
	GetWorld()->GetTimerManager().ClearTimer(SlowMoCDHandle);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	GetWorld()->GetTimerManager().SetTimer(SlowMoCDHandle,this,&UAC_ItemStorage::SlowMoRecharge,SlowMoDelay,true);
	}
}

void UAC_ItemStorage::SlowMoRecharge()
{
	SlowMoCharge+=SlowMoMomentCost/20;
	if(ItemStorageUI)
	ItemStorageUI->UpdateSlowMoCharge(SlowMoCharge);
	if(SlowMoCharge>=1)
	GetWorld()->GetTimerManager().ClearTimer(SlowMoCDHandle);

}

void UAC_ItemStorage::StaminaUse(float Cost)
{
	Stamina-=Cost;
	if(ItemStorageUI)
	ItemStorageUI->UpdateStaminaCharge(Stamina/100);
	GetWorld()->GetTimerManager().SetTimer(StaminaRestoreTimer,this,&UAC_ItemStorage::StaminaRestore,3,false);
}

void UAC_ItemStorage::StaminaRestore()
{
	if(!this && !GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(RestoreTimer,this,&UAC_ItemStorage::StaminaRestoreTimerFunc,0.5,true);
}

void UAC_ItemStorage::StaminaRestoreTimerFunc()
{
	if(Stamina<100)
	 {
      Stamina+=10;
	  if(ItemStorageUI)
	  ItemStorageUI->UpdateStaminaCharge(Stamina/100);
	 }
	 if(Stamina>=100)
	 {
	 Stamina=100;
	 GetWorld()->GetTimerManager().ClearTimer(RestoreTimer);
	 }
}

void UAC_ItemStorage::NewGadget(const FItemStorageData &NewRow)
{
	if(NewRow.StaticStruct())
	{
	FItemStorageData* NewItem = new FItemStorageData(NewRow);
	GadgetsArray.Add(NewItem);
	OnItemStorageUpdated.Broadcast(NewRow,GadgetsArray.Num());
	}
}


/*
UI part
*/
void UAC_ItemStorage::OpenInventory()
{
 if(InventoryUI)
	{
		InventoryUI->SetVisibility(ESlateVisibility::Visible);
		// Switch to inventory controlling
		if(GetOwner()->GetInstigatorController()->GetClass()->ImplementsInterface(UINF_MainController::StaticClass()))
		IINF_MainController::Execute_InterfaceSetInputModeUIOnly(GetOwner()->GetInstigatorController());

		bInventoryIsOpen=true;
	}	
}

void UAC_ItemStorage::CloseInventory()
{
	if(InventoryUI)
	{
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
		//Switch to game controlling
		if(GetOwner()->GetInstigatorController()->GetClass()->ImplementsInterface(UINF_MainController::StaticClass()))
		IINF_MainController::Execute_InterfaceSetInputModeGameOnly(GetOwner()->GetInstigatorController());

		bInventoryIsOpen=false;
	}
}

void UAC_ItemStorage::OnExtraGadgetChoosed(FItemStorageData& NewGadgetData, class UUserWidget* ButtonWidget)
{
	CloseInventory();
	//Memory safe
	if(!ButtonWidget)
	UE_LOG(LogTemp, Display, TEXT("You dont have button"));
	CurrentExtraGadget=nullptr;
	CurrentExtraGadgetButton=nullptr;
	if(CurrentExtraGadgetMechanic)
	{
	IINF_GadgetMechanic::Execute_CustomDestroy(Cast<UObject>(CurrentExtraGadgetMechanic));
	}

	CurrentExtraGadget=&NewGadgetData;
	CurrentExtraGadgetButton=ButtonWidget;
	if(CurrentExtraGadget->GadgetMechanic)
	{
	CurrentExtraGadgetMechanic=GetWorld()->SpawnActor<AActor>(CurrentExtraGadget->GadgetMechanic);
	CurrentExtraGadgetMechanic->SetOwner(GetOwner());
	}
	if(ItemStorageUI && CurrentExtraGadget->Icon)
	{
		ItemStorageUI->SetExtraGadgetImage(Cast<UUW_GadgetButton>(ButtonWidget)->GetCurrentButtonIcon());
	}
}

void UAC_ItemStorage::UseExtraGadget()
{
	if(CurrentExtraGadget && CurrentExtraGadgetMechanic&& CurrentExtraGadgetButton)
	{
	   if(GadgetsInCD.Contains(CurrentExtraGadget)&& !IINF_GadgetMechanic::Execute_GetInUsageStatus(Cast<UObject>(CurrentExtraGadgetMechanic))) return;

	   IINF_GadgetMechanic::Execute_UseGadget(Cast<UObject>(CurrentExtraGadgetMechanic));
       if(IINF_GadgetMechanic::Execute_GetInUsageStatus(Cast<UObject>(CurrentExtraGadgetMechanic))) return;
    
	/*
	Cooldown System
	*/
    UTexture2D* CDIcon=CurrentExtraGadget->CDIcon;
	UTexture2D* StandardIcon=CurrentExtraGadget->Icon;

	if(CDIcon&& ItemStorageUI)
	{
		UE_LOG(LogTemp, Display, TEXT("in cd icon"));
		ItemStorageUI->SetExtraGadgetImage(CDIcon);
		Cast<UUW_GadgetButton>(CurrentExtraGadgetButton)->SetButtonIcon(CDIcon);
	}

	FTimerHandle CDTimer;
	FItemStorageData* TempExtraGadget=CurrentExtraGadget;
	UUW_GadgetButton* TempGadgetButton=Cast<UUW_GadgetButton>(CurrentExtraGadgetButton);

	GadgetsInCD.Add((TempExtraGadget));
    if(GetWorld() &&TempExtraGadget )
	GetWorld()->GetTimerManager().SetTimer(CDTimer,[this,StandardIcon,TempExtraGadget,TempGadgetButton]()
	{
		CooldownTimer(StandardIcon,TempExtraGadget,TempGadgetButton);
	},CurrentExtraGadget->CDTime,false);
	}
	
}

void UAC_ItemStorage::CooldownTimer(UTexture2D *StandardIcon, FItemStorageData *TempExtraGadget, UUW_GadgetButton *TempGadgetButton)
{
	if(!this || !TempExtraGadget||!StandardIcon||!TempGadgetButton || GadgetsInCD.IsEmpty()) return;
		
		if(GadgetsInCD.Contains(TempExtraGadget))
		GadgetsInCD.Remove((TempExtraGadget));

		if(StandardIcon && TempGadgetButton && ItemStorageUI&&TempExtraGadget)
	  {
		if(CurrentExtraGadget==TempExtraGadget)
		ItemStorageUI->SetExtraGadgetImage(StandardIcon);
		
		
		TempGadgetButton->SetButtonIcon(StandardIcon);

	  }
}

void UAC_ItemStorage::ChooseGadgetWithKey(float Key)
{
	if(Key<0 ||Key>GadgetsArray.Num()-1) return;
	if(!GadgetsArray[Key]) return;
	UE_LOG(LogTemp, Display, TEXT("Your key %f"),Key);
	CloseInventory();
	//Memory safe
	CurrentExtraGadget=nullptr;
	CurrentExtraGadgetButton=nullptr;
	if(CurrentExtraGadgetMechanic)
	{
	IINF_GadgetMechanic::Execute_CustomDestroy(Cast<UObject>(CurrentExtraGadgetMechanic));
	}
	CurrentExtraGadget=GadgetsArray[Key];
	CurrentExtraGadgetButton=Cast<UUW_Inventory>(InventoryUI)->GetGadgetButtonByKey(Key);
	if(CurrentExtraGadget->GadgetMechanic)
	{
	CurrentExtraGadgetMechanic=GetWorld()->SpawnActor<AActor>(CurrentExtraGadget->GadgetMechanic);
	CurrentExtraGadgetMechanic->SetOwner(GetOwner());
	}
	if(ItemStorageUI && CurrentExtraGadget->Icon)
	{
		Cast<UUW_ItemStorage>(ItemStorageUI)->SetExtraGadgetImage(Cast<UUW_GadgetButton>(CurrentExtraGadgetButton)->GetCurrentButtonIcon());
	}
}

/*
Interface functions
*/
float UAC_ItemStorage::GetSlowMoCount_Implementation()
{
    return SlowMoCharge;
}

void UAC_ItemStorage::InventoryOnItemStorageUpdated(const FItemStorageData& NewRow,const float Key)
{
  Cast<UUW_Inventory>(InventoryUI)->OnItemStorageUpdated(NewRow,Key);
}
