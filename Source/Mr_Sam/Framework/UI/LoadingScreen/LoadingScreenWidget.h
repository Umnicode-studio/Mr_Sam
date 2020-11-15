// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"

#include "../../Core/Globals.h"

#include "LoadingScreenWidget.generated.h"

/**
* 
*/
UCLASS()
class MR_SAM_API ULoadingScreenWidget : public UUserWidget
{
    GENERATED_BODY()

    
public:
    ULoadingScreenWidget(const FObjectInitializer &ObjectInitializer);

    // API:
    UFUNCTION(BlueprintCallable, Category="Framework|LoadingScreen|Widget")
    void RemoveFromGameViewport(UGameViewportClient *ViewportClient);
    
    // Events:
    UFUNCTION(BlueprintImplementableEvent, Category="Framework|LoadingScreen|Widget")
    void OnScreenAppear();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Framework|LoadingScreen|Widget")
    void OnScreenDisappear(UGameViewportClient *ViewportClient);
};