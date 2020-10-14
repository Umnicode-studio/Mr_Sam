//
// Created by anton on 6/9/20.
//

#pragma once

#include "CoreMinimal.h"

#include "Generator/BaseGenerator.h"

#include "MapGenerator.generated.h"

UCLASS(Blueprintable)
class MR_SAM_API UDefaultMapGenerator : public UBaseGenerator {
    GENERATED_BODY()
public:
    UDefaultMapGenerator();

protected:
    virtual bool Init(UMapOutput *Output) override;
    virtual void CleanUp(UMapOutput *Output) override;

    // ---
    virtual void GenerateRooms(UMapOutput *Output) override;
    virtual void GeneratePasses(UMapOutput *Output) override;
    virtual void SetRoomFlags(UMapOutput *Output) override;
    virtual void PlaceStructures(UMapOutput *Output) override;
};