// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticActor.h"

AStaticActor::AStaticActor()
{
	PrimaryActorTick.bCanEverTick = false;   
}
void AStaticActor::BeginPlay()
{
	Super::BeginPlay();	
}

void AStaticActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

