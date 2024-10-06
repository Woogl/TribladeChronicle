// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TcAbilitySystemComponent.generated.h"

class UTcPawnData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityInputTriggerEvent, FGameplayTag, InputTag);

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API UTcAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UTcAbilitySystemComponent();

	void InitializeAbilitySystem(UTcPawnData* InPawnData, AActor* InOwnerActor);
	void UninitializeAbilitySystem();
	
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

public:
	/** Delegate fired when our pawn becomes the ability system's avatar actor */
	FSimpleMulticastDelegate OnAbilitySystemInitialized;

	/** Delegate fired when our pawn is removed as the ability system's avatar actor */
	FSimpleMulticastDelegate OnAbilitySystemUninitialized;
	
protected:
	void TryActivateAbilitiesOnSpawn();
	
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

protected:
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};
