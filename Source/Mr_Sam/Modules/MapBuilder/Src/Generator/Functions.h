// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "../IO/MapInput.h"
#include "../IO/MapOutput.h"

//#include "../Utils/Structures/Structures.hpp"
//#include "../Utils/Structures/Nodes.hpp"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Containers/Map.h"

#include "Functions.generated.h"

USTRUCT(BlueprintType)
struct MR_SAM_API FRoomNeighbor
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TEnumAsByte<ESideEnum> Side = S_Up;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    UMapRoom *Room = nullptr;
};

UCLASS()
class MR_SAM_API UGeneratorUtils : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|Functions")
    static TArray<FRoomNeighbor> GetRoomNeighbors(UMapRoom *Room, UMapOutput *Output);

    
    /*static bool IsRoomProtected(UMapRoom *Room, const PlacedStructure &Structure, const PlacedStructureVector &PlacedVector,
    const MapInput &Input, MapOutput &Output); */

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|Functions")
    static bool IsStepsHere(const FString StepsId, const FIntPoint Position, UMapOutput *Output);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|Functions")
    static bool IsWallHere(const FString WallId, const FIntPoint Position, UMapOutput *Output);

    // ---
    //static void ProceedFlagNode(MapRoom *Room, MapOutput &Output, FlagNode *Node = nullptr);
    //static void ProceedProtectNode(ProtectNodeParams Parameters);

    // ---
    //static Utils::Sides GetSidesConfigForArea(MapRoom *Room, Range <Data_2 <int32>> Area,
                                              //MapOutput &Output);
};