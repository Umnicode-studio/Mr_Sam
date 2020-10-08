//
// Created by anton on 8/25/2020.
//

#pragma once

#include "CoreMinimal.h"

#include "MapItem.h"
#include "../Utils/MapKeyFunc.h"

#include "MapItemOutputArray.generated.h"

UCLASS(BlueprintType)
class MR_SAM_API UMapItemOutputArray : public UMapObject {
    GENERATED_BODY()
    
    TMultiMap <FIntPoint *, int, FDefaultSetAllocator,
                               TMultiMapKeyFuncIntPointP<int>> PositionRefsBook;

    void LinkItem(UMapItemOutput *Item);
    bool FixBrokenLinks(bool Remove = false); // Work around that can help update pointers in
                                              // maps when vector has been relocated
public:
    UMapItemOutputArray();

    // Variables:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
    TArray<UMapItemOutput *> Content;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
    int LastCapacity = 0;
    
    // API:
    /*UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray",
     *meta = (WorldContext = WorldContextObject))
    bool AddItem(UObject *WorldContextObject, TSubclassOf<UMapItemOutput> ItemClass); */

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    bool AddItem(TSubclassOf<UMapItemOutput> ItemClass);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    bool AddExistItem(UMapItemOutput *Item);
    
    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    bool RemoveItem(FIntPoint Position, UMapLayer *Layer); 

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    int GetSize() const;

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    bool Empty() const;

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    UMapItemOutput *GetItemByIndex(int Index);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    TArray <UMapItemOutput *> GetItemsByPosition(FIntPoint Position);

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    UMapItemOutput *FindItem(FIntPoint Position, UMapLayer *Layer);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    UMapItemOutput *FindItemThatPossesPoint(FIntPoint Point, UMapLayer *Layer); 

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    TArray <UMapItemOutput *> &GetContent();
};