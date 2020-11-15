// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "Runtime/UMG/Public/UMG.h"
#include "Animation/WidgetAnimation.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "../../Core/Globals.h"

#include "MenuUtils.generated.h"

class UMenuUtils;

UCLASS(BlueprintType)
class MR_SAM_API UMenuScreenSwapper final : public UObject
{
    GENERATED_BODY()
public:
    UMenuScreenSwapper();
    ~UMenuScreenSwapper();
    
    // API:
    UFUNCTION(BlueprintCallable, Category="Framework|UI|Menu|SwapScreen")
    UWidgetAnimation* const GetScreenAppearAnimation() const;

    UFUNCTION(BlueprintCallable, Category="Framework|UI|Menu|SwapScreen")
    UWidgetAnimation* const GetScreenDisappearAnimation() const;

    UFUNCTION(BlueprintCallable, Category="Framework|UI|Menu|SwapScreen")
    bool IsHolderValid() const;

    // Event listeners:
    UFUNCTION()
    void DisappearAnimationFinished_Listener();

    UFUNCTION()
    void AppearAnimationFinished_Listener();

protected:
    // Hidden initializer. Without calling it swapper will not work
    bool Init(UUserWidget *NWidget,
              UWidgetAnimation *AppearAnimation,
              UWidgetAnimation *DisappearAnimation);

    UPROPERTY()
    UUserWidget *Widget = nullptr;
    
    UPROPERTY()
    UWidgetAnimation *AppearAnim = nullptr;

    UPROPERTY()
    UWidgetAnimation *DisappearAnim = nullptr;
    
    bool IsInitedCorrectly = false;
    
    friend class UMenuUtils;
};

/**
* 
*/
UCLASS()
class MR_SAM_API UMenuUtils : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Framework|UI|Menu", meta=(WorldContext="Widget"))
    static void SwapMenuScreen(UUserWidget *Widget,
                               UWidgetAnimation *AppearAnimation,
                               UWidgetAnimation *DisappearAnimation,
                               UMenuScreenSwapper *&Swapper,
                               bool &Result);
};