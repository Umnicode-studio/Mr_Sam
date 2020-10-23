// Fill out your copyright notice in the Description page of Project Settings.

#include "Stage.h"

FVector AStage::GetActorScaleToTile(const FVector &ActorSize, const FIntPoint &ItemSize) const
{
	if (ActorSize == FVector::ZeroVector) return FVector::ZeroVector;
	
	return (this->TileSize * FVector(1.0f, ItemSize.X, ItemSize.Y)) / ActorSize;
}
float AStage::GetZValueForActor(const TArray<UMapLayer *> &Layers)
{
	float Median = 0;

	int c = 0;
	for (; c < Layers.Num(); c++)
	{
		if (IsValid(Layers[c]))
		{
			Median += Layers[c]->ZOffset;
		}
	}

	return Median / (c + 1);
}

AStage::AStage()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Create new root component
	this->StageRootComponent = CreateDefaultSubobject<USceneComponent> ("StageRoot");
	this->StageRootComponent->SetMobility(EComponentMobility::Static);
	
	this->RootComponent = this->StageRootComponent; 
}

bool AStage::LoadStage(UMapOutput* Output)
{
	if (IsValid(Output) && Output->IsGeneratedSuccessfully)
	{
		// Load static level
		// Clean
		if (this->StageTiles.Num() != 0)
		{
			for (int c = 0; c < this->StageTiles.Num(); ++c)
			{
				if (IsValid(this->StageTiles[c]))
				{
					FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, true);
					this->StageTiles[c]->DetachFromActor(Rules);
					
					this->StageTiles[c]->Destroy();
				}
			}
			this->StageTiles.Empty(); 
		}

		// Add new items
		for (UMapItemOutput *Item : Output->Items->GetContent())
		{	
			if (IsValid(Item))
			{	
				if (Item->IsMapTile()) // If map tile
				{
					const FVector MeshSize = UFrameworkUtils::GetStaticMeshSize(
						                     static_cast <AStaticMeshActor* >
						                        (Item->Actor)->GetStaticMeshComponent()->GetStaticMesh());
					
					const FIntPoint ItemPos = Output->Input->Size - Item->Position;
					FVector ItemLocation = this->GetActorLocation() +
						                         FVector(GetZValueForActor(Item->Layers),
						                         	     ItemPos.X * this->TileSize.X,
						                         	     ItemPos.Y * this->TileSize.Y);

					ItemLocation.Y -= (this->TileSize.Y * Item->Size.X) / 2;
					ItemLocation.Z -= (this->TileSize.Z * Item->Size.Y);

					// Set item transforms
					FTransform ItemTransform;
					
					ItemTransform.SetLocation(ItemLocation);
					ItemTransform.SetRotation(FQuat(0, 0, 0, 0));
					ItemTransform.SetScale3D(this->GetActorScaleToTile(MeshSize, Item->Size));
					
					// If item is map tile, we know that Item->Actor is StaticMeshActor
					AStaticMeshActor *Actor = GetWorld()->SpawnActor<AStaticMeshActor>(
						                                         Item->Actor->GetClass(), ItemTransform);
						
					// Attach tile to stage
					FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, true);
					Actor->AttachToActor(this, Rules);
					
					Actor->SetMobility(EComponentMobility::Static); 
					
					this->StageTiles.Add(Actor); 
				}
			}
		}

		return true;
	}

	return false;
}

void AStage::BeginPlay()
{
	Super::BeginPlay();
}

void AStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}