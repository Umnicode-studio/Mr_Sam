//
// Created by anton on 5/31/20.
//

#pragma once

#include "CoreMinimal.h"

#include "../Utils/MapObject.h"
#include "../Layer/MapLayer.h"
#include "../Structure/MapStructure.h"

#include "MapInput.generated.h"

UCLASS(Blueprintable)
class MR_SAM_API UMapInput : public UMapObject {
    GENERATED_BODY()
public:
    // Map settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString LevelName = "None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString LevelDescription = "None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Chapter")
    int ChapterNumber = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Chapter")
    int LevelNumber = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    bool MergeWalls = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FIntPoint Size;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Doors")
    FIntPoint StartPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Doors")
    FIntPoint FinishPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Defaults|Room")
    int MinRoomWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Defaults|Room")
    int MaxRoomWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Defaults|Room")
    int RoomHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Defaults")
    int StepWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Defaults")
    int BorderSize;

    // Default items
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Defaults")
    TSubclassOf<UMapItem> WallItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Defaults")
    TSubclassOf<UMapItem> WallWithHoleItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Defaults")
    TSubclassOf<UMapItem> StepsItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Defaults")
    TSubclassOf<UMapItem> DoorItem;

    // Content
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Content")
    TArray<TSubclassOf<UMapStructure>> Structures; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Content")
    TArray<TSubclassOf<UMapLayer>> Layers; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Content")
    TSubclassOf<UMapLayer> DefaultLayer; 
};