// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "Generator/BaseGenerator.h"
#include "../../../Framework/Utils/CppUtils.h"

#include "MapGenerator.generated.h"

UENUM()
enum EOverlappedPassType
{
    T_None = 0     UMETA(DisplayName="None"),
    T_Current = 1  UMETA(DisplayName="Current"),
    T_Target = 2   UMETA(DisplayName="Target"),
    T_Both = 3     UMETA(DisplayName="Both")
};

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

    virtual void MergeWalls(UMapOutput* Output) override;
    
    virtual void SetRoomFlags(UMapOutput *Output) override;
    virtual void PlaceStructures(UMapOutput *Output) override;
};