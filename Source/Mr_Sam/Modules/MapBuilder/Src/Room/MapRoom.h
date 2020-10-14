//
// Created by anton on 6/6/20.
//

#pragma once

#include "CoreMinimal.h"

#include "../Utils/MapObject.h"
#include "../Utils/Structures/Sides.h"

#include "MapRoom.generated.h"

USTRUCT(BlueprintType)
struct MR_SAM_API FRoomPass{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int RoomId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TEnumAsByte<ESideEnum> Side = S_Up;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FIntPoint Position;

    FRoomPass()
    {
        this->RoomId = 0;
    }
    explicit FRoomPass(const int RoomId)
    {
        this->RoomId = RoomId;
    }
};

UENUM()
enum ERoomFlags{
    R_Finish        UMETA(DisplayName="Finish"),
    R_Start         UMETA(DisplayName="Start"),
    R_Deadend       UMETA(DisplayName="Deadend"),
    R_Mainpath      UMETA(DisplayName="Mainpath")
};

USTRUCT(BlueprintType)
struct FRoomCoordinates
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int PositionOnFloor = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int Floor = 0;
    
    FRoomCoordinates()
    {
       
    }

    FRoomCoordinates(const int PositionOnFloor, const int Floor)
    {
        this->PositionOnFloor = PositionOnFloor;
        this->Floor = Floor;
    }
    
    bool operator== (const FRoomCoordinates &Right) const
    {
        return this->PositionOnFloor == Right.PositionOnFloor && this->Floor == Right.Floor;
    }
};

UCLASS(Blueprintable)
class MR_SAM_API UMapRoom : public UMapObject {
    GENERATED_BODY()
public:
    // Properties:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray <TEnumAsByte<ERoomFlags>> Flags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Bounds")
    int Width = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Bounds")
    FIntPoint Start;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Bounds")
    FIntPoint Finish;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int GlobalPosition = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FRoomCoordinates Coordinates;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TArray<FRoomPass> Passes;

    UMapRoom();
    
    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoom")
    void AddFlag(const ERoomFlags Flag);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoom")
    bool IsHaveFlag(const ERoomFlags Flag) const;

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoom",
              meta = (WorldContext = WorldContextObject))
    static UMapRoom *MAKE(UObject *WorldContextObject, const int RoomWidth,
                          const FIntPoint RoomStart, const FIntPoint RoomFinish, 
                          const int RoomGlobalPosition, const FRoomCoordinates RoomCoordinates);
    
    // ---
    virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
};