// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Benchmark.generated.h"

UENUM()
enum EBenchmarkShapeType
{
	Line       UMETA(DisplayName="Line"),
    Plane2D    UMETA(DisplayName="Plane 2D"),
    Cube       UMETA(DisplayName="Cube"),
};

UCLASS()
class MR_SAM_API ABenchmark : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	USceneComponent *BenchRootComponent;

	void CreateComponents();
	void AddComponent(FVector Location);
public:	
	ABenchmark();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Properties")
	TArray<UStaticMeshComponent *> Components;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	FVector Size = FVector(1, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	int SpaceBetweenObjects = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	UStaticMesh *Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	TEnumAsByte<EBenchmarkShapeType> ShapeType = Line;

    #if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
    #endif
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
