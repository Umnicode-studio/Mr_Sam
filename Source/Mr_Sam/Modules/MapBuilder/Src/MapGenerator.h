//
// Created by anton on 6/9/20.
//

#pragma once

#include "CoreMinimal.h"

#include "Generator/BaseGenerator.h"

#include "MapGenerator.generated.h"

UCLASS(Blueprintable)
class UDefaultMapGenerator : public UBaseGenerator {
    GENERATED_BODY()
    
    // Primitive items
    UPROPERTY()
    UMapItemInput *WallItem = nullptr;

    UPROPERTY()
    UMapItemInput *WallHole = nullptr;

    UPROPERTY()
    UMapItemInput *StepsItem = nullptr;

    UPROPERTY()
    UMapItemInput *DoorItem = nullptr;
public:
    UDefaultMapGenerator();

protected:
    void Init(UMapOutput *Output) override;
    void CleanUp(UMapOutput *Output) override;
    
    void GenerateRooms(UMapOutput *Output) override;
    void GeneratePasses(UMapOutput *Output) override;
    void SetRoomFlags(UMapOutput *Output) override;
    void PlaceStructures(UMapOutput *Output) override;
};