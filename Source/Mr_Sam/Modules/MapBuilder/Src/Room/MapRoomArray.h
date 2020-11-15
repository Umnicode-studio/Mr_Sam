// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "MapRoom.h"
#include "../Utils/PtrLess.h"

#include "MapRoomArray.generated.h"

UCLASS(BlueprintType)
class MR_SAM_API UMapRoomArray : public UMapObject {
    GENERATED_BODY()

    std::map <int32 *, int32, FPtrLessIntPtr> GlobalPositionRefsBook;
    std::map <FRoomCoordinates *, int32, FPtrLessRoomCoordinatesPtr> CoordinatesRefsBook;
    
    void LinkRoom(UMapRoom *Room);
    bool FixBrokenLinks(const bool Remove = false); // Work around that can help update pointers in
                                                    // maps when array has been relocated
public:
    UMapRoomArray(); 

    // Variables:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
    int32 LastCapacity = 0;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
    TArray <UMapRoom *> Content;
    
    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray", meta = (WorldContext = WorldContextObject))
    bool AddRoom(UObject *WorldContextObject, TSubclassOf<UMapRoom> RoomClass);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool AddExistRoom(UMapRoom *Room);

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool RemoveRoomByGlobalPosition(int32 GlobalPosition);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool RemoveRoomByCoordinates(FRoomCoordinates Coordinates);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool RemoveItemByIndex(int32 Index);

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    int32 Num() const;

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool Empty() const;

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    UMapRoom *GetRoomByIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    UMapRoom *GetRoomByGlobalPosition(int32 GlobalPosition);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    UMapRoom *GetRoomByCoordinates(FRoomCoordinates Coordinates);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    TArray <UMapRoom *> GetRoomsOnFloor(int32 Floor);  

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    TArray <UMapRoom *> &GetContent();
};