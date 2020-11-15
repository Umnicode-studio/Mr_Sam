#include "MenuUtils.h"

// --- UMenuScreenSwapper
UMenuScreenSwapper::UMenuScreenSwapper()
{
    
}
UMenuScreenSwapper::~UMenuScreenSwapper()
{
    
}

// API:
UWidgetAnimation* const UMenuScreenSwapper::GetScreenAppearAnimation() const
{
    return this->AppearAnim;
}
UWidgetAnimation* const UMenuScreenSwapper::GetScreenDisappearAnimation() const
{
    return this->DisappearAnim;
}

bool UMenuScreenSwapper::IsHolderValid() const
{
    return this->IsInitedCorrectly &&
           IsValid(this->AppearAnim) &&
           IsValid(this->DisappearAnim) &&
           IsValid(this->Widget);
}

// Events:
void UMenuScreenSwapper::DisappearAnimationFinished_Listener()
{
    if (this->IsHolderValid())
    {
        // Unbind from disappear animation 
        FWidgetAnimationDynamicEvent DisappearAnimationEvent;
        DisappearAnimationEvent.BindDynamic(this, &UMenuScreenSwapper::DisappearAnimationFinished_Listener);
        
        this->Widget->UnbindFromAnimationFinished(this->DisappearAnim, DisappearAnimationEvent);

        // Bind event to appear animation
        FWidgetAnimationDynamicEvent AppearAnimationEvent;
        AppearAnimationEvent.BindDynamic(this, &UMenuScreenSwapper::AppearAnimationFinished_Listener);

        this->Widget->BindToAnimationFinished(this->AppearAnim, AppearAnimationEvent);
        
        // Play appear animation
        this->Widget->PlayAnimationForward(this->AppearAnim);
    }
}

void UMenuScreenSwapper::AppearAnimationFinished_Listener()
{
    if (this->IsHolderValid())
    {
        // Unbind from appear animation
        FWidgetAnimationDynamicEvent AppearAnimationEvent;
        AppearAnimationEvent.BindDynamic(this, &UMenuScreenSwapper::AppearAnimationFinished_Listener);
        
        this->Widget->UnbindFromAnimationFinished(this->AppearAnim, AppearAnimationEvent);
    }
}

// Hidden part
bool UMenuScreenSwapper::Init(UUserWidget *NWidget,
                              UWidgetAnimation* AppearAnimation,
                              UWidgetAnimation* DisappearAnimation)
{
    this->IsInitedCorrectly = false;

    // Checks
    if (!IsValid(NWidget))
    {
        UE_LOG(LogFramework, Error, TEXT("MenuScreenSwapper: NWidget is not valid"));
        return false;
    }

    if (!IsValid(AppearAnimation))
    {
        UE_LOG(LogFramework, Error, TEXT("MenuScreenSwapper: Appear animation is not valid"));
        return false;
    }
    
    if (!IsValid(DisappearAnimation))
    {
        UE_LOG(LogFramework, Error, TEXT("MenuScreenSwapper: Disappear animation is not valid"));
        return false;
    }

    // Assign variables 
    this->Widget = NWidget;
        
    this->AppearAnim = AppearAnimation;
    this->DisappearAnim = DisappearAnimation;

    // Bind to animation finish
    FWidgetAnimationDynamicEvent DisappearAnimationEvent;
    DisappearAnimationEvent.BindDynamic(this, &UMenuScreenSwapper::DisappearAnimationFinished_Listener);

    this->Widget->BindToAnimationFinished(this->DisappearAnim, DisappearAnimationEvent);

    // Play animation
    this->Widget->PlayAnimationReverse(this->DisappearAnim);

    this->IsInitedCorrectly = true;
    return true;
}

// --- UMenuUtils
void UMenuUtils::SwapMenuScreen(UUserWidget* Widget,
                                UWidgetAnimation* AppearAnimation,
                                UWidgetAnimation* DisappearAnimation,
                                UMenuScreenSwapper *&Swapper,
                                bool &Result)
{
    UMenuScreenSwapper *Holder = NewObject<UMenuScreenSwapper>(Widget);
    
    Result = Holder->Init(Widget, AppearAnimation, DisappearAnimation);
    Swapper = Holder;
}