// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TcHealthComponent.generated.h"

struct FGameplayEffectSpec;
class UTcHealthSet;
class UTcAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTcHealth_DeathEvent, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FTcHealth_AttributeChanged, UTcHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

/**
 *	Defines current state of death.
 */
UENUM(BlueprintType)
enum class ETcDeathState : uint8
{
	NotDead = 0,
	DeathStarted,
	DeathFinished
};

/**
 *	An actor component used to handle anything related to health.
 */
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class TRIBLADECHRONICLE_API UTcHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTcHealthComponent();
	
	// Returns the health component if one exists on the specified actor.
	UFUNCTION(BlueprintPure, Category = "TC|Health")
	static UTcHealthComponent* FindHealthComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UTcHealthComponent>() : nullptr); }

	// Initialize the component using an ability system component.
	UFUNCTION(BlueprintCallable, Category = "TC|Health")
	void InitializeWithAbilitySystem(UTcAbilitySystemComponent* InASC);

	// Uninitialize the component, clearing any references to the ability system.
	UFUNCTION(BlueprintCallable, Category = "TC|Health")
	void UninitializeFromAbilitySystem();

	// Returns the current health value.
	UFUNCTION(BlueprintCallable, Category = "TC|Health")
	float GetHealth() const;

	// Returns the current maximum health value.
	UFUNCTION(BlueprintCallable, Category = "TC|Health")
	float GetMaxHealth() const;

	// Returns the current health in the range [0.0, 1.0].
	UFUNCTION(BlueprintCallable, Category = "TC|Health")
	float GetHealthNormalized() const;

	UFUNCTION(BlueprintCallable, Category = "TC|Health")
	ETcDeathState GetDeathState() const { return DeathState; }

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "TC|Health", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	bool IsDeadOrDying() const { return (DeathState > ETcDeathState::NotDead); }

	// Begins the death sequence for the owner.
	UFUNCTION(BlueprintCallable)
	virtual void StartDeath();

	// Ends the death sequence for the owner.
	UFUNCTION(BlueprintCallable)
	virtual void FinishDeath();

public:
	// Delegate fired when the health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FTcHealth_AttributeChanged OnHealthChanged;

	// Delegate fired when the max health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FTcHealth_AttributeChanged OnMaxHealthChanged;

	// Delegate fired when the death sequence has started.
	UPROPERTY(BlueprintAssignable)
	FTcHealth_DeathEvent OnDeathStarted;

	// Delegate fired when the death sequence has finished.
	UPROPERTY(BlueprintAssignable)
	FTcHealth_DeathEvent OnDeathFinished;

protected:
	virtual void OnUnregister() override;

	virtual void HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);

	UFUNCTION()
	virtual void OnRep_DeathState(ETcDeathState OldDeathState);

public:
	// Ability system used by this component.
	UPROPERTY()
	TWeakObjectPtr<UTcAbilitySystemComponent> AbilitySystemComponent;

	// Health set used by this component.
	UPROPERTY()
	TObjectPtr<const UTcHealthSet> HealthSet;

	// Replicated state used to handle dying.
	UPROPERTY(ReplicatedUsing = OnRep_DeathState)
	ETcDeathState DeathState = ETcDeathState::NotDead;
};
