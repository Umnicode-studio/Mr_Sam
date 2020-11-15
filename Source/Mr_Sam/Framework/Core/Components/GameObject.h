// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../SmartVariable/SmartInt.h"

#include "GameObject.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MR_SAM_API UGameObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGameObjectComponent();

	// Properties:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
    FString Label = "undefined";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	bool IsInteractive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	bool IsPickupAble = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Physics")
	int Damage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Physics")
    FSmartInt Health {100};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Physics")
    bool IsBurn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties|Physics")
    bool IsExplode = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties|Interaction")
    bool IsInInteract = false;

protected:
	
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
