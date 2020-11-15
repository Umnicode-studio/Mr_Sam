#include "LoadingScreenWidget.h"

ULoadingScreenWidget::ULoadingScreenWidget(const FObjectInitializer& ObjectInitializer)
                                                                         : UUserWidget(ObjectInitializer)
{
    
}

// API:
void ULoadingScreenWidget::RemoveFromGameViewport(UGameViewportClient* ViewportClient)
{
    if (!IsValid(ViewportClient))
    {
        UE_LOG(LogFramework, Error, TEXT("RemoveFromViewport: Viewport client is invalid"))
        return;
    }

    ViewportClient->RemoveViewportWidgetContent(this->TakeWidget());
}

// Events:
void ULoadingScreenWidget::OnScreenDisappear_Implementation(UGameViewportClient* ViewportClient)
{
    this->RemoveFromGameViewport(ViewportClient);
}