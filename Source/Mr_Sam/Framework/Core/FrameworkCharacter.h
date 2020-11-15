// (c) DPACK.inc

#pragma once

#include "CoreMinimal.h"

#include "Components/GameObject.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "FrameworkCharacter.generated.h"

// Death rules:
USTRUCT(BlueprintType)
struct FDeathRules
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	bool DisableInput = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	bool EnableRagdoll = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	USkeletalMeshComponent *RagdollMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	bool ChangeHealthSilently = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	int NewHealth = 0;
};

USTRUCT(BlueprintType)
struct FAutoDeathRules
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	bool IsEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	int MinimalHealth = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	FDeathRules DeathRules;
};

// 

UCLASS(Blueprintable)
class MR_SAM_API AFrameworkCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFrameworkCharacter();

	// Properties:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Properties|Interaction")
	bool IsInInteraction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	UGameObjectComponent *GameObject = nullptr;
	
protected:
	UPROPERTY()
	FAutoDeathRules AutoDeathRules;
	
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Events: 
	UFUNCTION(BlueprintImplementableEvent)
    void OnAction(const FString &ActionId);

	UFUNCTION(BlueprintImplementableEvent)
    void OnDeath();

	// Functions:
	
	// Death API:
	UFUNCTION(BlueprintCallable, Category="Framework|GameCharacter")
	virtual void Death(const FDeathRules Rules);

	// Auto death:
	UFUNCTION(BlueprintCallable, Category="Framework|GameCharacter")
	void SetAutoDeathRules(const FAutoDeathRules Rules);

	UFUNCTION(BlueprintCallable, Category="Framework|GameCharacter")
	FAutoDeathRules GetAutoDeathRules() const;

	UFUNCTION()
	void AutoDeath_HealthListener(int Health);
};