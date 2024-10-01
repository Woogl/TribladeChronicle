// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TcAbilitySystemComponent.generated.h"

class UTcGameplayAbility;
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

	UPROPERTY(BlueprintAssignable, Category = "TC|Input")
	FOnAbilityInputTriggerEvent OnAbilityInputPressed;

	UPROPERTY(BlueprintAssignable, Category = "TC|Input")
	FOnAbilityInputTriggerEvent OnAbilityInputReleased;
	
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

	UPROPERTY(BlueprintReadWrite)
	TMap<UTcGameplayAbility*, int32> ComboAbilityIndexes;

protected:
	void TryActivateAbilitiesOnSpawn();
	
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

protected:
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};
