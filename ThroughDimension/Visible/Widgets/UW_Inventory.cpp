// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Inventory.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/Visible/Widgets/UW_GadgetButton.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_ItemStorage.h"
#include "C:\Users\user\Documents\Unreal Projects\ThroughDimension\Source\ThroughDimension\Visible\ItemStorageData.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainController.h"

void UUW_Inventory::NativeConstruct()
{
    Super::NativeConstruct();
    SetVisibility(ESlateVisibility::Hidden);

}


void UUW_Inventory::OnItemStorageUpdated(const FItemStorageData& NewRow,const float Key)
{
    // Implementating new button by FItemStorageData
    TSoftObjectPtr<UUW_GadgetButton> TempPtr=NewObject<UUW_GadgetButton>(GetWorld(),ButtonTemplate);
    if(TempPtr.Get())
    {
    GadgetButtons.Add(TempPtr.Get());
    AddNewButton(NewRow,TempPtr,Key);
    TempPtr.Get()->OnGadgetButtonClickedWithParam.AddUObject(this,&UUW_Inventory::OnGadgetButtonClicked);
    }
    
}

void UUW_Inventory::AddNewGadget()
{
}

void UUW_Inventory::AddNewButton(const FItemStorageData &NewRow, TSoftObjectPtr<UUserWidget> BindButtonPtr,const float Key)
{
    // Creating UI Button
    UUW_GadgetButton* GadgetButton = Cast<UUW_GadgetButton>(BindButtonPtr.Get());
    GadgetButton->FunctionalData=NewRow;
    // Adding new button to inventory
    if(MainWrapBox && GadgetButton)
     {
        GadgetButton->SetButtonKey(Key);
       // GadgetButton->SetRenderScale(FVector2D(3, 3));
      MainWrapBox->AddChild(GadgetButton);
     }
     
}

void UUW_Inventory::OnGadgetButtonClicked(UUW_GadgetButton* Button)
{
    if(Button)
    UE_LOG(LogTemp, Display, TEXT("button clicked"));
 UE_LOG(LogTemp, Display, TEXT("gadget used %s"),*Button->FunctionalData.GadgetName.ToString());
 // Custom delegate for ItemStorageComponent 
 OnGadgetChoosed.Broadcast(Button->FunctionalData,Button);
   if(GetVisibility()==ESlateVisibility::Visible)
   {
   SetVisibility(ESlateVisibility::Hidden);
   }

   if(GetOwningPlayer()->GetClass()->ImplementsInterface(UINF_MainController::StaticClass()))
	IINF_MainController::Execute_InterfaceSetInputModeGameOnly(GetOwningPlayer());
}

void UUW_Inventory::OpenInventory()
{
    
		UE_LOG(LogTemp, Warning, TEXT("opening closing"));
		SetVisibility(ESlateVisibility::Hidden);
		if(GetOwningPlayer()->GetInstigatorController()->GetClass()->ImplementsInterface(UINF_MainController::StaticClass()))
        IINF_MainController::Execute_InterfaceSetInputModeGameOnly(GetOwningPlayer()->GetInstigatorController());

}
