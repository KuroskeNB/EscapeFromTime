// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_MainHUD.h"
#include "Components/TextBlock.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_MainChar.h"
#include "C:/Users/user/Documents/Unreal Projects/ThroughDimension/Source/ThroughDimension/NotVisible/Interfaces/INF_Gun.h"

void UUW_MainHUD::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
Super::NativeTick(MyGeometry,InDeltaTime);
if(AmmoCount && GetOwningPlayerPawn()&& GetOwningPlayerPawn()->GetClass()->ImplementsInterface(UINF_MainChar::StaticClass()))
    {
        if(IINF_MainChar::Execute_GetGun(GetOwningPlayerPawn())&&IINF_MainChar::Execute_GetGun(GetOwningPlayerPawn())->GetClass()->ImplementsInterface(UINF_Gun::StaticClass()))
        {
        float CurrentAmmoCountfloat=IINF_Gun::Execute_GetCurrentAmmoCount(IINF_MainChar::Execute_GetGun(GetOwningPlayerPawn()));
        float MaxAmmoCountfloat=IINF_Gun::Execute_GetMaxAmmoCount(IINF_MainChar::Execute_GetGun(GetOwningPlayerPawn()));
        AmmoCount->SetText(FText::FromString(FString::Printf(TEXT("%.f/%.f"),CurrentAmmoCountfloat,MaxAmmoCountfloat)));
        }
    }
}

void UUW_MainHUD::NativeConstruct()
{
    Super::NativeConstruct();
}
