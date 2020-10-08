// Fill out your copyright notice in the Description page of Project Settings.

#include "Stage.h"

AStage::AStage()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStage::BeginPlay()
{
	Super::BeginPlay();
}

void AStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}