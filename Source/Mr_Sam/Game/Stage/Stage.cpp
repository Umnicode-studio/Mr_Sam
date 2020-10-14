// Fill out your copyright notice in the Description page of Project Settings.

#include "Stage.h"

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
					const FVector MeshSize = UFrameworkUtils::GetStaticMeshSize(static_cast <AStaticMeshActor* >
						                                         (Item->Actor)->GetStaticMeshComponent()->GetStaticMesh());
					
					// If item is map tile, we know that Item->Actor is StaticMeshActor
					AStaticMeshActor *Actor = GetWorld()->SpawnActor<AStaticMeshActor>(
						                                             Item->Actor->GetClass(),
						                                             this->GetActorLocation() +
						                                                     FVector(Item->Position.X * MeshSize.X,
                                                                                     0,
                                                                                     Item->Position.Y * MeshSize.Z),
                                                                     FRotator(0, 0, 0));
						
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