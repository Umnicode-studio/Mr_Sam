// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MapTile.generated.h"

/**
 * 
 */
UCLASS()
class MR_SAM_API AMapTile : public AStaticMeshActor
{
	GENERATED_BODY()

public:
    // World size is changes in Stage::LoadLevel(), but this used for set item size for steps, etc..
    UFUNCTION( BlueprintImplementableEvent, Category = "MapBuilder|MapTile|Events")
    void UpdateItemSize(const FIntPoint Size);
};
