// (c) DPACK.inc

#include "Registry.h"

URegistry::URegistry(const FObjectInitializer& ObjectInitializer)
                                               : UGameInstance(ObjectInitializer)
{
    
}

// API:
TArray<const UGameObjectComponent*> URegistry::GetGameObjects() const
{
    TArray<const UGameObjectComponent *> Components;
    for (const UGameObjectComponent *Component : this->GameObjects)
    {
        Components.Add(Component);
    }

    return Components;
}