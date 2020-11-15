// (c) DPACK.inc


#include "FrameworkUtils.h"
#include "Kismet/GameplayStatics.h"

void UFrameworkUtils::IsActorGameObject(AActor* Actor, bool &Result, UGameObjectComponent *&GameObject)
{
    if (!Actor)
    {
        Result = false;
    }else
    {
        GameObject = dynamic_cast <UGameObjectComponent *> (Actor->GetComponentByClass(UGameObjectComponent::StaticClass()));
        Result = IsValid(GameObject);
    }
}

FVector UFrameworkUtils::GetStaticMeshSize(UStaticMesh *Mesh)
{
    if (!IsValid(Mesh)) return FVector::ZeroVector;
    
    return Mesh->GetBounds().GetBox().GetSize();
}