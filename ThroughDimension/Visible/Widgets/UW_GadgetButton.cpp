// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_GadgetButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "C:\Users\user\Documents\Unreal Projects\ThroughDimension\Source\ThroughDimension\Visible\ItemStorageData.h"


void UUW_GadgetButton::OnTheButtonClicked()
{
    OnGadgetButtonClickedWithParam.Broadcast(this);
}

void UUW_GadgetButton::SetButtonKey(float Key)
{
   
     ButtonKeyFloat=Key;

}

void UUW_GadgetButton::SetButtonIcon(UTexture2D *NewIcon)
{
    if(TheButton&& NewIcon &&TheButton->GetStyle().StaticStruct())
    {   
     FButtonStyle ButtonStyle = TheButton->GetStyle();
     FSlateBrush ImageBrush;
    
     ImageBrush.SetResourceObject(NewIcon);


        ButtonStyle.Normal = ImageBrush;
        ButtonStyle.Hovered = ImageBrush;
        ButtonStyle.Pressed = ImageBrush;
     TheButton->SetStyle(ButtonStyle);
     CurrentIcon=NewIcon;
    }
}

void UUW_GadgetButton::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry,InDeltaTime);
    if(ButtonKey)
    {
    ButtonKey->SetText(FText::FromString(FString::Printf(TEXT("%.f"), ButtonKeyFloat)));
    }
}

void UUW_GadgetButton::NativeConstruct()
{
    Super::NativeConstruct();
    UE_LOG(LogTemp, Display, TEXT("gadgetbutton contruct"));
    if(TheButton&& FunctionalData.StaticStruct())
    {   
        TheButton->OnPressed.AddDynamic(this,&UUW_GadgetButton::OnTheButtonClicked);
     FButtonStyle ButtonStyle = TheButton->GetStyle();
     FSlateBrush ImageBrush;
     if(FunctionalData.Icon)
     {
     ImageBrush.SetResourceObject(FunctionalData.Icon);


        // Устанавливаем изображение для нажатого и отпущенного состояния
        ButtonStyle.Normal = ImageBrush;
        ButtonStyle.Hovered = ImageBrush;
        ButtonStyle.Pressed = ImageBrush;
     TheButton->SetStyle(ButtonStyle);
     CurrentIcon=FunctionalData.Icon;
     }
    }
}
