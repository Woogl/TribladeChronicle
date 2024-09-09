// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "TcPlayerState.generated.h"

class UTcAbilitySystemComponent;
class UAbilitySystemComponent;
class UTcHealthSet;

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATcPlayerState();

	UFUNCTION(BlueprintCallable, Category = "Tc|PlayerState")
	UTcAbilitySystemComponent* GetTcAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	TObjectPtr<const UTcHealthSet> GetHealthSet() const { return HealthSet; }
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTcAbilitySystemComponent> AbilitySystemComponent;

	// Health attribute set used by this actor.
	UPROPERTY()
	TObjectPtr<const UTcHealthSet> HealthSet;
};
