// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticActor.generated.h"

UCLASS()
class MR_SAM_API AStaticActor : public AActor
{
	GENERATED_BODY()
public:	
	AStaticActor();
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
