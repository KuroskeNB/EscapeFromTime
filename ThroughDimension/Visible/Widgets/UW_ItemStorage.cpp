// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ItemStorage.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_ItemStorage.h"

void UUW_ItemStorage::SetExtraGadgetImage(UTexture2D *Icon)
{
    if(ExtraGadgetImage)
    {
        ExtraGadgetImage->SetBrushFromTexture(Icon);
    }
}

void UUW_ItemStorage::UpdateSlowMoCharge(float Charge)
{
    if(Charge>1)Charge=1;
    
    if(SlowMoCharge)
    {
     SlowMoCharge->SetPercent(Charge);
    }
}

void UUW_ItemStorage::UpdateStaminaCharge(float Charge)
{
    if(Charge>1)Charge=1;
    if(StaminaCharge)
    {
     StaminaCharge->SetPercent(Charge);
    }
}

void UUW_ItemStorage::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry,InDeltaTime);
    if(SlowMoCount && GetOwningPlayerPawn()&&GetOwningPlayerPawn()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    {
        if(IINF_MainChar::Execute_GetItemStorage(GetOwningPlayerPawn())->GetClass()->ImplementsInterface(UINF_ItemStorage::StaticClass()))
        {
        float SlowMoCountfloat=IINF_ItemStorage::Execute_GetSlowMoCount(IINF_MainChar::Execute_GetItemStorage(GetOwningPlayerPawn()));
        SlowMoCount->SetText(FText::FromString(FString::Printf(TEXT("%f"),SlowMoCountfloat)));
        }
    }
}

void UUW_ItemStorage::NativeConstruct()
{
    Super::NativeConstruct();
    if(SlowMoCount && GetOwningPlayerPawn()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    {
        if(IINF_MainChar::Execute_GetItemStorage(GetOwningPlayerPawn())->GetClass()->ImplementsInterface(UINF_ItemStorage::StaticClass()))
        {
        float SlowMoCountfloat=IINF_ItemStorage::Execute_GetSlowMoCount(IINF_MainChar::Execute_GetItemStorage(GetOwningPlayerPawn()));
        SlowMoCount->SetText(FText::FromString(FString::Printf(TEXT("%f"),SlowMoCountfloat)));
        }
    }
    if(SlowMoCharge)
    {
     SlowMoCharge->SetPercent(1.f);
    }
    if(StaminaCharge)
    {
     StaminaCharge->SetPercent(1.f);
    }
}
