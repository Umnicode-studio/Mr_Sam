//
// Created by anton on 8/23/2020.
//

#pragma once

#include "CoreMinimal.h"

#include "MapRoom.h"
#include "../Utils/PtrLess.h"

#include "MapRoomArray.generated.h"

UCLASS(BlueprintType)
class MR_SAM_API UMapRoomArray : public UMapObject {
    GENERATED_BODY()

    std::map <int *, int, FPtrLessIntPtr> GlobalPositionRefsBook;
    std::map <FRoomCoordinates *, int, FPtrLessRoomCoordinatesPtr> CoordinatesRefsBook;
    
    void LinkRoom(UMapRoom *Room);
    bool FixBrokenLinks(const bool Remove = false); // Work around that can help update pointers in
                                                    // maps when array has been relocated
public:
    UMapRoomArray(); 

    // Variables:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
    int LastCapacity = 0;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
    TArray <UMapRoom *> Content;
    
    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray", meta = (WorldContext = WorldContextObject))
    bool AddRoom(UObject *WorldContextObject, TSubclassOf<UMapRoom> RoomClass);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool AddExistRoom(UMapRoom *Room);

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool RemoveRoomByGlobalPosition(int GlobalPosition);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool RemoveRoomByCoordinates(FRoomCoordinates Coordinates);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool RemoveItemByIndex(int Index);

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    int Num() const;

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    bool Empty() const;

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    UMapRoom *GetRoomByIndex(int Index);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    UMapRoom *GetRoomByGlobalPosition(int GlobalPosition);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    UMapRoom *GetRoomByCoordinates(FRoomCoordinates Coordinates);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    TArray <UMapRoom *> GetRoomsOnFloor(int Floor);  

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapRoomArray")
    TArray <UMapRoom *> &GetContent();
};