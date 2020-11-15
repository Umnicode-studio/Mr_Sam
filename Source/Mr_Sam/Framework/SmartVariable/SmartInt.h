// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "../Core/Globals.h"

#include "SmartInt.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIntChangedDelegate, int, NewValue);

class USmartIntBlueprintTools;

UCLASS(BlueprintType)
class USmartIntDelegateHolder : public UObject
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable)
    FIntChangedDelegate OnValueChanged;
};

// Data-holder and cpp methods of SmartInt type
USTRUCT(BlueprintType)
struct FSmartInt
{
    GENERATED_BODY()
    
    FSmartInt();
    FSmartInt(const int InitialValue);
    
    ~FSmartInt();

    // Properties:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int InitialValue = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    bool IsCallDelegate = true;

    // Cpp API:
    void SetValue(UObject *WorldContextObject, int NewValue, bool ChangeSilently = false);
    int &GetValue();

    USmartIntDelegateHolder *GetDelegateHolder(UObject *WorldContextObject);

    // Operators:
    operator int();
    
protected:
    int VariableValue = 0;
    bool IsVariableInited = false;

    UPROPERTY()
    USmartIntDelegateHolder *DelegateHolder = nullptr;
    
    friend class USmartIntBlueprintTools;
};

// Blueprint access of FSmartInt methods. Proxy for FSmartInt cpp methods
UCLASS()
class MR_SAM_API USmartIntBlueprintTools final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Framework|SmartInt", meta=(WorldContext="WorldContextObject"))
    static void SetValue(UObject *WorldContextObject,
                         const int NewValue, UPARAM(ref) FSmartInt &Variable, FSmartInt &OutVariable);
    
    UFUNCTION(BlueprintPure, Category="Framework|SmartInt")
    static int GetValue(UPARAM(ref) FSmartInt &Variable);

    UFUNCTION(BlueprintPure, Category="Framework|SmartInt", meta=(WorldContext="WorldContextObject"))
    static USmartIntDelegateHolder *GetDelegateHolder(UObject *WorldContextObject,
                                                      UPARAM(ref) FSmartInt &Variable);
};