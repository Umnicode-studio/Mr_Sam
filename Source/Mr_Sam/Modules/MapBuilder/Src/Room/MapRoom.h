// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "../Utils/MapObject.h"
#include "../Utils/Structures/Sides.h"

#include "MapRoom.generated.h"

USTRUCT(BlueprintType)
struct MR_SAM_API FRoomPass{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int32 RoomId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    TEnumAsByte<ESideEnum> Side = S_Up;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FIntPoint Position;

    FRoomPass()
    {
        this->RoomId = 0;
    }
    explicit FRoomPass(const int32 RoomId, TEnumAsByte<ESideEnum> PassSide, FIntPoint PassPosition)
    {
        this->RoomId = RoomId;
        this->Side = PassSide;
        this->Position = PassPosition;
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
    int32 PositionOnFloor = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int32 Floor = 0;
    
    FRoomCoordinates()
    {
       
    }

    FRoomCoordinates(const int32 PositionOnFloor, const int32 Floor)
    {
        this->PositionOnFloor = PositionOnFloor;
        this->Floor = Floor;
    }

    FString ToString() const
    {
        return "Position on floor: " + FString::FromInt(this->PositionOnFloor) + " Floor: " +
               FString::FromInt(this->Floor);
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
    int32 Width = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Bounds")
    FIntPoint Start;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Bounds")
    FIntPoint Finish;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    int32 GlobalPosition = 0;
    
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
    static UMapRoom *MAKE(UObject *WorldContextObject, const int32 RoomWidth,
                          const FIntPoint RoomStart, const FIntPoint RoomFinish, 
                          const int32 RoomGlobalPosition, const FRoomCoordinates RoomCoordinates);
    
    // ---
    #if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
    #endif
};