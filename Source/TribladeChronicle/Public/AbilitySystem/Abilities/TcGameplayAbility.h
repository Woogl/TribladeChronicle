// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TcGameplayAbility.generated.h"

class UInputAction;

/**
 *  The base gameplay ability class used by this project.
 */
UCLASS(Abstract, Meta = (ShortTooltip = "The base gameplay ability class used by this project."))
class TRIBLADECHRONICLE_API UTcGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UTcGameplayAbility();

	// Tells an ability to activate immediately when it's granted. (Useful for passive abilities and abilities forced on others)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom Gameplay Ability")
	bool ActivateAbilityOnGranted = false;

	// Which Input Action to bind the activation event to.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	UInputAction* ActivationInputAction = nullptr;
	
protected:
	// Keep a pointer to "Avatar Character" so we don't have to cast to Character in instanced abilities owned by a Character derived class.
	TWeakObjectPtr<ACharacter> AvatarCharacter = nullptr;
	
	// Think of this as "BeginPlay".
	// Add logic here that should run when the Ability is first initialized.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	// Called to bind Input Pressed and Input Released events to the Avatar Actor's Enhanced Input Component if it is reachable. 
	void SetupEnhancedInputBindings(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);

	// Called when the "Activation Input Action" is triggered.
	void HandleInputPressedEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpecHandle SpecHandle);

	// Called when the "Activation Input Action" is completed.
	void HandleInputReleasedEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpecHandle SpecHandle);

	// Override "OnRemoveAbility" to clean up Enhanced Input Bindings.
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
