#include "SmartInt.h"

// --- FSmartInt ---
FSmartInt::FSmartInt()
{
}
FSmartInt::FSmartInt(const int InitialValue)
{   
    this->InitialValue = InitialValue;
}

FSmartInt::~FSmartInt()
{
}

// Cpp API:
void FSmartInt::SetValue(UObject *WorldContextObject, int NewValue, bool ChangeSilently)
{
    this->VariableValue = NewValue;

    if (this->IsCallDelegate && !ChangeSilently)
    {
        this->GetDelegateHolder(WorldContextObject)->OnValueChanged.Broadcast(NewValue);
    }
}
int &FSmartInt::GetValue()
{
    // Init variable ( workaround for PostInitProperties )
    if (!this->IsVariableInited)
    {
        this->VariableValue = this->InitialValue;
        this->IsVariableInited = true;
    }

    return this->VariableValue;
}

USmartIntDelegateHolder* FSmartInt::GetDelegateHolder(UObject* WorldContextObject)
{
    // Create DelegateHolder only when it needed
    if (!IsValid(this->DelegateHolder))
    {   
        this->DelegateHolder = NewObject<USmartIntDelegateHolder>(WorldContextObject);
        
        if (!IsValid(this->DelegateHolder))
        {
            UE_LOG(LogFramework, Error, TEXT("FSmartInt: Failed to create Delegate holder"))
            return nullptr;
        }
    }

    return this->DelegateHolder;
}

// ---
FSmartInt::operator int()
{
    return this->GetValue();
}

// --- USmartIntBlueprintTools ---
void USmartIntBlueprintTools::SetValue(UObject *WorldContextObject,
                                       const int NewValue, FSmartInt& Variable, FSmartInt& OutVariable)
{
    Variable.SetValue(WorldContextObject, NewValue);
    OutVariable = Variable;
}
int USmartIntBlueprintTools::GetValue(FSmartInt &Variable)
{
    return Variable.GetValue();
}

USmartIntDelegateHolder* USmartIntBlueprintTools::GetDelegateHolder(UObject* WorldContextObject,
                                                                    FSmartInt& Variable)
{
    return Variable.GetDelegateHolder(WorldContextObject);
}
