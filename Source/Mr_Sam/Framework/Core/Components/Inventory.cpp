#include "Inventory.h"

#include "Serialization/StructuredArchiveFormatter.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventory::SelectCell(int CellIndex)
{
	if (!this->IsValidIndex(CellIndex))
	{
		return false;
	}

	this->SelectedCell = CellIndex;
	return true;
}

bool UInventory::PushObjectToInventory(AActor* Actor)
{
	return false;
}
bool UInventory::PushObjectToCell(AActor* Actor, int CellIndex)
{
	if (IsValid(Actor) && IsValidIndex(CellIndex))
	{
		this->InventoryCells[CellIndex].ItemsCount++;
	}

	return false;
}

bool UInventory::TakeObjectFromSelectedCell()
{
	return false;
}
bool UInventory::TakeObjectFromCell(int CellIndex)
{
	return false;
}

void UInventory::UpdateInventorySize(FInventoryCell Default)
{
	if (this->InventorySize > -1)
	{
		
	}
}


void UInventory::BeginPlay()
{
	Super::BeginPlay();
	this->UpdateInventorySize(FInventoryCell()); // Check inventory
}
bool UInventory::IsValidIndex(int CellIndex) const
{
	return (CellIndex > -1 && CellIndex < this->InventorySize);
}
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

