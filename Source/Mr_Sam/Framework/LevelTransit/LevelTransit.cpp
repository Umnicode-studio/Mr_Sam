// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelTransit.h"


#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

bool ULevelTransit::LoadGameLevel(UObject *WorldContextObject, const FName LevelName)
{
    if (LevelName != "" && IsValid(WorldContextObject))
    {
        URegistry *Registry = Cast<URegistry>(UGameplayStatics::GetGameInstance(WorldContextObject));

        if (IsValid(Registry))
        {
            UUserWidget *Widget = CreateWidget<UUserWidget>(Registry,
                            Registry->LevelTransitWidgetClass->GetClass());

            APlayerController *Controller = UGameplayStatics::GetPlayerControllerFromID(WorldContextObject, 0);

            if (IsValid(Widget) && IsValid(Controller))
            {
                Widget->SetOwningPlayer(Controller);
                Widget->AddToViewport();
            
                UGameplayStatics::OpenLevel(WorldContextObject, LevelName);
        
                UE_LOG(LogTemp, Warning, TEXT("Load game level"));
            }
            {
                UE_LOG(LogTemp, Warning, TEXT("Something not valid")); // TODO: 
            }
            
            //Widget->RemoveFromParent();
            
            return true;
        }
    }
    
    return false;
}
