// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"

#include "../../Core/Globals.h"
#include "../../Utils/CppUtils.h"

#include "TipWidget.generated.h"

USTRUCT(BlueprintType)
struct FTipWidgetEditorProperties
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool PlayPreview = false;
};

/**
* 
*/
UCLASS()
class MR_SAM_API UTipWidget : public UTextBlock
{
    GENERATED_BODY()

    int TipIndex = 0;
    
    float OldTipChangeDelay = 0.0f;
    bool OldPlayPreview = false;
    
    FTimerHandle TimerHandle;
    void ResetTimer();
public:
    UTipWidget(const FObjectInitializer &ObjectInitializer);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Content")
    TArray <FText> Tips;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Content")
    float TipChangeDelay = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Content")
    FTipWidgetEditorProperties EditorProperties;

    // API:
    UFUNCTION(BlueprintCallable, Category="Framework|LoadingScreen|TipWidget")
    void SetRandomTip(bool Shuffle = true, bool ResetTimer = true);
    
    // ---
    UFUNCTION(BlueprintCallable, Category="Framework|LoadingScreen|TipWidget")
    bool SetTipIndex(int Index, bool ResetTimer = true);
    
    UFUNCTION(BlueprintCallable, Category="Framework|LoadingScreen|TipWidget")
    int GetTipIndex() const;

    // ---
    UFUNCTION(BlueprintCallable, Category="Framework|LoadingScreen|TipWidget")
    void ShuffleTips();

    // Events implementation
    virtual void OnWidgetRebuilt() override;
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    
    void TipTimer_Listener();
};