// (c) DPACK.inc

#include "FrameworkGameMode.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

void AFrameworkGameMode::RemoveLoadingScreenWidgets()
{
    UWorld *World = this->GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogFramework, Error, TEXT("StartPlay: World is invalid"))
        return;
    }
        
    UGameViewportClient *ViewportClient = World->GetGameViewport();
    if (!IsValid(ViewportClient))
    {
        UE_LOG(LogFramework, Error, TEXT("StartPlay: Viewport client is invalid"))
        return;
    }
    
    TArray<UUserWidget *> Widgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(World, Widgets,
                                                  this->LoadingScreenWidgetClass, false);

    for (UUserWidget *Widget : Widgets)
    {
        ULoadingScreenWidget *LoadingWidget = dynamic_cast<ULoadingScreenWidget *> (Widget);
        if (IsValid(LoadingWidget))
        {
            LoadingWidget->OnScreenDisappear(ViewportClient);
        }
    }
}

AFrameworkGameMode::AFrameworkGameMode()
{
}

void AFrameworkGameMode::StartPlay()
{
    Super::StartPlay();

    // Remove all loading screen widgets from viewport
    if (UGameplayStatics::HasOption(this->OptionsString, "LoadingScreen"))
    {
        this->RemoveLoadingScreenWidgets();
    }
}

// API:
bool AFrameworkGameMode::LoadGameLevel(FName LevelName, float MinimumDelay)
{
    // Checks
    if (!IsValid(GEngine))
    {
        UE_LOG(LogFramework, Error, TEXT("LoadGameLevel: GEngine is not exist"))
        return false;
    }

    FString LevelNameString = LevelName.ToString();
    if (!GEngine->MakeSureMapNameIsValid(LevelNameString))
    {
        UE_LOG(LogFramework, Error, TEXT("LoadGameLevel: Map {%s} is not exist"), *LevelNameString)
        return false;
    }

    if (IsValid(this->LoadingScreenWidget))
    {
        UE_LOG(LogFramework, Warning, TEXT("LoadGameLevel: There is another level loading"))
        return false;
    }

    if (!IsValid(this->LoadingScreenWidgetClass->GetClass()))
    {
        UE_LOG(LogFramework, Error, TEXT("LoadGameLevel: Loading screen widget class is invalid"))
        return false;
    }

    UWorld *World = this->GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogFramework, Error, TEXT("LoadGameLevel: World is invalid"))
        return false;
    }
    
    APlayerController *Controller = UGameplayStatics::GetPlayerControllerFromID(World, 0);
    
    // Create widget
    this->LoadingScreenWidget = CreateWidget <ULoadingScreenWidget> (Controller,
                                              this->LoadingScreenWidgetClass);

    if (!IsValid(this->LoadingScreenWidget)){
        UE_LOG(LogFramework, Error, TEXT("LoadGameLevel: Created widget is invalid"))
        return false;
    }

    // Get viewport
    UGameViewportClient *GameViewportClient = World->GetGameViewport();   
    if (!IsValid(GameViewportClient))
    {
        UE_LOG(LogFramework, Error, TEXT("LoadGameLevel: Game viewport client is invalid"))
        return false;
    }

    GameViewportClient->AddViewportWidgetContent(this->LoadingScreenWidget->TakeWidget(), 999);
    this->LoadingScreenWidget->OnScreenAppear();
    
    this->LoadingLevelName = LevelName;
                
    // Delay between AddToViewportWidgetContent and level loading
    FTimerHandle Handle;
    World->GetTimerManager().SetTimer(Handle, this,
                                      &AFrameworkGameMode::LoadGameLevel_Listener, MinimumDelay);
            
    return true;
}

// Events:
void AFrameworkGameMode::LoadGameLevel_Listener() const
{
    UWorld *World = this->GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogFramework, Error, TEXT("LoadGameLevel_Listener: World is invalid"))
        return;
    }
    
    UGameplayStatics::OpenLevel(World, this->LoadingLevelName, true, "LoadingScreen=1");
}