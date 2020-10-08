#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"

#include "LevelTransitWidget.generated.h"

/**
* 
*/
UCLASS()
class MR_SAM_API ULevelTransitWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    ULevelTransitWidget(const FObjectInitializer &ObjectInitializer);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    float LoadingPercent = 0.1;
};