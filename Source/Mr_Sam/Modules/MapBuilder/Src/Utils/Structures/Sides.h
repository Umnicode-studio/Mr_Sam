// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"
#include "Sides.generated.h"

UENUM()
enum ESideType{
    St_Open    UMETA(DisplayName="Open"),
    St_Close   UMETA(DisplayName="Close"),
    St_Any     UMETA(DisplayName="Any")
};

UENUM()
enum ESideEnum{
    S_Up      UMETA(DisplayName="Up"),
    S_Down    UMETA(DisplayName="Down"),
    S_Left    UMETA(DisplayName="Left"),
    S_Right   UMETA(DisplayName="Right")
};

USTRUCT(BlueprintType)
struct MR_SAM_API FSides {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TEnumAsByte<ESideType> Up;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TEnumAsByte<ESideType> Down;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TEnumAsByte<ESideType> Left; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TEnumAsByte<ESideType> Right; 
    
    FSides()
    {
        Up = Down = Left = Right = St_Close;
    }

    explicit FSides(const ESideType Up, const ESideType Down, const ESideType Left, const ESideType Right)
    {
        this->Up = Up;
        this->Down = Down;
        this->Left = Left;
        this->Right = Right; 
    }
};