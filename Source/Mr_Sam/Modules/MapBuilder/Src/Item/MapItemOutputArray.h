// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "MapItemOutput.h"
#include "../Utils/PtrLess.h"

#include "MapItemOutputArray.generated.h"

UCLASS(BlueprintType)
class MR_SAM_API UMapItemOutputArray : public UMapObject {
    GENERATED_BODY()

    using FMultiMap = std::multimap <FIntPoint *, int32, FPtrLessIntPointPtr>;
    using FIteratorRange = std::pair <FMultiMap::iterator, FMultiMap::iterator>;
    
    FMultiMap PositionRefsBook;

    void LinkItem(UMapItemOutput *Item);
    bool FixBrokenLinks(bool Remove = false); // Work around that can help update pointers in
                                              // maps when vector has been relocated
public:
    UMapItemOutputArray();

    // Variables:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
    TArray<UMapItemOutput *> Content;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
    int32 LastCapacity = 0;
    
    // API:
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray", meta = (WorldContext = WorldContextObject))
    bool AddItem(UObject *WorldContextObject, TSubclassOf<UMapItemOutput> ItemClass);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    bool AddExistItem(UMapItemOutput *Item);
    
    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    bool RemoveItemByPosition(FIntPoint Position, UMapLayer *Layer);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    bool RemoveItemsById(FIntPoint Position, const FString Id);
    
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    bool RemoveItemByIndex(int32 Index);

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    int32 Num() const;

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    bool Empty() const;

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    UMapItemOutput *GetItemByIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    TArray <UMapItemOutput *> GetItemsByPosition(FIntPoint Position);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    TArray<UMapItemOutput *> GetItemsByPositionAndId(FIntPoint Position, FString Id);

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    UMapItemOutput *FindItem(FIntPoint Position, UMapLayer *Layer);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    UMapItemOutput *FindItemThatPossesPointByLayer(FIntPoint Point, UMapLayer *Layer);

    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    TArray <UMapItemOutput *> FindItemsThatPossesPointById(FIntPoint Point, FString Id);

    // ---
    UFUNCTION(BlueprintCallable, Category="MapBuilder|MapItemOutputArray")
    TArray <UMapItemOutput *> &GetContent();
};