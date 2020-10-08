// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct MR_SAM_API FInventoryCell
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString ItemId = "Undefined";

	UPROPERTY(BlueprintReadOnly)
	int ItemsCount = 0;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsLocked = false;

	UPROPERTY(BlueprintReadWrite)
	int MaxItemsAmount = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MR_SAM_API UInventory : public UActorComponent
{
	GENERATED_BODY()

	void UpdateInventorySize(FInventoryCell Default);
public:	
	UInventory();

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
	TArray <FInventoryCell> InventoryCells;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties")
	int SelectedCell = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	int InventorySize = 0;

	// API:
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool SelectCell(int CellIndex);

	// ---
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool PushObjectToInventory(AActor *Actor);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool PushObjectToCell(AActor *Actor, int CellIndex);

	// ---
	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TakeObjectFromSelectedCell();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TakeObjectFromCell(int CellIndex);
protected:
	virtual void BeginPlay() override;
	bool IsValidIndex(int CellIndex) const;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
