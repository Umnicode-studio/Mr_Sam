// Fill out your copyright notice in the Description page of Project Settings.

#include "Benchmark.h"
#include "FrameworkUtils.h"

void ABenchmark::CreateComponents()
{	
	const FVector MeshSize = UFrameworkUtils::GetStaticMeshSize(this->Mesh) +
		FVector(this->SpaceBetweenObjects, this->SpaceBetweenObjects, this->SpaceBetweenObjects);
	
	if (MeshSize != FVector::ZeroVector)
	{
		// Clean
		if (this->Components.Num() != 0)
		{
			for (int c = 0; c < this->Components.Num(); ++c)
			{
				if (IsValid(this->Components[c]))
				{
					FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, true);
					this->Components[c]->DetachFromComponent(Rules);
		
					this->Components[c]->UnregisterComponent();
					this->Components[c]->DestroyComponent();

					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
					//  TEXT("Some debug message!"));
				}
			}
			this->Components.Empty(); 
		} 
		
		switch (this->ShapeType)
		{
		case Line:
			for (int c = 0; c < this->Size.X; ++c)
			{
				const FVector Location = FVector( MeshSize.X * (c), 0, 0);
				this->AddComponent(Location);
			}
			break;
		case Plane2D:
			{
				for (int x = 0; x < this->Size.X; ++x)
				{
					for (int y = 0; y < this->Size.Y; ++y)
					{
						this->AddComponent(
                             FVector(MeshSize.X * x, MeshSize.Y * y, 0));
					}
				}
			
				break;
			}
		default: // Cube
			{
				for (int x = 0; x < this->Size.X; ++x)
				{
					for (int y = 0; y < this->Size.Y; ++y)
					{
						for (int z = 0; z < this->Size.Z; ++z)
						{
							this->AddComponent(
                                FVector(MeshSize.X * x, MeshSize.Y * y, MeshSize.Y * z));
						}
					}
				}
				
				break;
			}
		}
	}
}

void ABenchmark::AddComponent(FVector Location)
{
	const FString ComponentName = "BenchMesh_" + FString::FromInt(this->Components.Num());
	UStaticMeshComponent *Component = NewObject<UStaticMeshComponent>
                                    (this, *ComponentName);

	Component->RegisterComponent();
	
	const FAttachmentTransformRules TransformRules(EAttachmentRule::KeepRelative, true);
	Component->AttachToComponent(this->GetRootComponent(), TransformRules);
	
	Component->SetRelativeLocation(Location);
	Component->SetStaticMesh(this->Mesh);
	Component->SetMobility(EComponentMobility::Static);

	this->Components.Add(Component);
}

ABenchmark::ABenchmark()
{
	PrimaryActorTick.bCanEverTick = true;

	this->BenchRootComponent = CreateDefaultSubobject <USceneComponent> (TEXT("Root"));
	
	this->BenchRootComponent->SetRelativeLocation(FVector(0, 0,0));
	this->BenchRootComponent->SetMobility(EComponentMobility::Static);
	
	this->RootComponent = BenchRootComponent;
}

#if WITH_EDITOR
void ABenchmark::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	this->CreateComponents();
}
#endif

void ABenchmark::BeginPlay()
{
	Super::BeginPlay();
	this->CreateComponents();
}

void ABenchmark::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

