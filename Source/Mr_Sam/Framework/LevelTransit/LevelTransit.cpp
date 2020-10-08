// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelTransit.h"


#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

bool ULevelTransit::LoadLevel(UObject *WorldContextObject, FName LevelName)
{
    if (LevelName != "")
    {
        URegistry *Registry = Cast<URegistry>(UGameplayStatics::GetGameInstance(WorldContextObject));

        if (Registry)
        {
            UUserWidget *Widget = CreateWidget<UUserWidget>(
                UGameplayStatics::GetGameInstance(WorldContextObject),
                            Registry->LevelTransitWidgetClass);

            Widget->AddToPlayerScreen();

            UGameplayStatics::OpenLevel(WorldContextObject, LevelName);

            Widget->RemoveFromViewport();
            return true;
        }
    }
    
    return false;
}
