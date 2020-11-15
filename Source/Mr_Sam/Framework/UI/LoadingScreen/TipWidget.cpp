#include "TipWidget.h"

void UTipWidget::ResetTimer()
{
    UWorld *World = this->GetWorld();
    if (!IsValid(World))
    {
        UE_LOG(LogFramework, Error, TEXT("ResetTimer: World is invalid"))
        return;
    }
   
    // Try to stop exist timer
    if (this->TimerHandle.IsValid())
    {
        World->GetTimerManager().ClearTimer(this->TimerHandle);
    }

    // Don't create new timer if we in UMG editor
    if (!World->IsGameWorld() && !this->EditorProperties.PlayPreview)
    {
        return;
    }

    // Create new timer
    this->TimerHandle = FTimerHandle();
            
    World->GetTimerManager().SetTimer(this->TimerHandle,
                                      this, &UTipWidget::TipTimer_Listener,
                                      this->TipChangeDelay, true);
}

UTipWidget::UTipWidget(const FObjectInitializer& ObjectInitializer)
                                                         : UTextBlock(ObjectInitializer)
{
}

// API:
void UTipWidget::SetRandomTip(bool Shuffle, bool ResetTimer)
{
    if (this->Tips.Num() > 0)
    {
        if (Shuffle) this->ShuffleTips();
        this->SetTipIndex(FMath::RandRange(0, this->Tips.Num() - 1), ResetTimer);
    }
}

// ---
bool UTipWidget::SetTipIndex(int Index, bool ResetTimer)
{
    if (Index > -1 && Index < this->Tips.Num())
    {
        this->SetText(this->Tips[Index]);
        this->TipIndex = Index;

        if (ResetTimer || OldTipChangeDelay != this->TipChangeDelay)
        {
            this->ResetTimer();
            this->OldTipChangeDelay = this->TipChangeDelay;
        }
        
        return true;
    }

    return false;
}
int UTipWidget::GetTipIndex() const
{
    return this->TipIndex;
}

// ---
void UTipWidget::ShuffleTips()
{
    FFrameworkCppUtils::ShuffleTArray(this->Tips);
}

// Events implementation:
void UTipWidget::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();
    
    this->SetRandomTip();
}
void UTipWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (this->EditorProperties.PlayPreview != this->OldPlayPreview)
    {
        if (!this->EditorProperties.PlayPreview)
        {
            this->ResetTimer();
        }else
        {
            this->SetRandomTip(false, true);
        }
        
        this->OldPlayPreview = this->EditorProperties.PlayPreview;
    }
}

void UTipWidget::TipTimer_Listener()
{
    this->SetRandomTip(false, false);
}