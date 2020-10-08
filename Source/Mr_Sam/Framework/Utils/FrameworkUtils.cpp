// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameworkUtils.h"
#include "Kismet/GameplayStatics.h"

void UFrameworkUtils::IsActorGameObject(AActor* Actor, bool &Result, UGameObject *&GameObject)
{
    if (!Actor)
    {
        Result = false;
    }else
    {
        GameObject = dynamic_cast <UGameObject *> (Actor->GetComponentByClass(UGameObject::StaticClass()));
        Result = IsValid(GameObject);
    }
}


void UFrameworkUtils::GetClosestInteractPawn(APawn* WorldContextObject, float MinDistance, APawn *&Pawn, float &Distance, UInteraction *&PawnInteraction,
                                             UGameObject *&PawnGameObject)
{
    Distance = -1;
    Pawn = nullptr;

    URegistry *Registry = dynamic_cast <URegistry *> (UGameplayStatics::GetGameInstance(WorldContextObject));

    if (Registry)
    {
        // Get all GameObjects in this World
        TArray<UGameObject *> FoundGameObjects = Registry->GameObjectsList;

        for (UGameObject *GameObject : FoundGameObjects)
        {
            if (IsValid(GameObject))
            {
                APawn *GamePawn = dynamic_cast<APawn *> (GameObject->GetOwner());
                if (IsValid(GamePawn))
                {
                    UInteraction *Interaction = dynamic_cast<UInteraction *> (GamePawn->GetComponentByClass(UInteraction::StaticClass()));

                    if (IsValid(Interaction))
                    {
                        // Measure distance
                        const float PawnDistance = (WorldContextObject->GetActorLocation() - GamePawn->GetActorLocation()).Size();
                        
                        if (PawnDistance >= MinDistance)
                        {
                            if (PawnDistance < Distance || Distance == -1)
                            {
                                // Set new closest Pawn
                                Pawn = GamePawn;
                                Distance = PawnDistance;
                                PawnInteraction = Interaction;
                                PawnGameObject = GameObject;
                            }
                        }
                    }
                }
            }
        }
    } 
}

/*void UFrameworkUtils::GetClosestActivePawn(AActor* WorldContextObject, float MinDistance, AActivePawn *&Actor, float &Distance)
{
    Distance = -1;
    
    TArray<AActor *> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(WorldContextObject->GetWorld(), AActivePawn::StaticClass(), FoundActors);

    for (AActor *FoundActor : FoundActors)
    {
        AActivePawn *ActiveActor = dynamic_cast<AActivePawn *>(FoundActor);
        if (ActiveActor)
        {
            const int ActorDistance = (WorldContextObject->GetActorLocation() - ActiveActor->GetActorLocation()).Size();

            if (ActorDistance >= MinDistance)
            {
                if (ActorDistance < Distance || Distance == -1)
                {
                    Actor = ActiveActor;
                    Distance = ActorDistance;
                }
            }
        }
    }
}   */

FVector UFrameworkUtils::GetStaticMeshSize(UStaticMesh *Mesh)
{
    if (!IsValid(Mesh)) return FVector::ZeroVector;

    return Mesh->GetBounds().GetBox().GetSize();
}
