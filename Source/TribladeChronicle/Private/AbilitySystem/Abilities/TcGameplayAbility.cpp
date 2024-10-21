// Copyright Woogle. All Rights Reserved.


#include "AbilitySystem/Abilities/TcGameplayAbility.h"

#include "EnhancedInputComponent.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "GameFramework/Character.h"

UTcGameplayAbility::UTcGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UTcGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	// Set the "Avatar Character" reference.
	AvatarCharacter = Cast<ACharacter>(ActorInfo->AvatarActor);

	// Set up Bindings for Enhanced Input.
	SetupEnhancedInputBindings(ActorInfo, Spec);

	// Try to Activate immediately if "Activate Ability On Granted" is true.
	if (ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}

void UTcGameplayAbility::SetupEnhancedInputBindings(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	if (IsValid(ActorInfo->AvatarActor.Get()))
	{
		if (const APawn* AvatarPawn = Cast<APawn>(ActorInfo->AvatarActor.Get()))
		{
			if (const AController* PawnController = AvatarPawn->GetController())
			{
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PawnController->InputComponent.Get()))
				{
					if (UTcGameplayAbility* AbilityInstance = Cast<UTcGameplayAbility>(Spec.Ability.Get()))
					{
						// If we have a valid "Input Pressed Trigger" type bind the pressed event.
						if (IsValid(AbilityInstance->ActivationInputAction))
						{
							EnhancedInputComponent->BindAction(AbilityInstance->ActivationInputAction, ETriggerEvent::Started, AbilityInstance, &ThisClass::HandleInputPressedEvent, ActorInfo, Spec.Handle);
							EnhancedInputComponent->BindAction(AbilityInstance->ActivationInputAction, ETriggerEvent::Completed, AbilityInstance, &ThisClass::HandleInputReleasedEvent, ActorInfo, Spec.Handle);
						}
					}
				}
			}
		}
	}
}

void UTcGameplayAbility::HandleInputPressedEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpecHandle SpecHandle)
{
	// Find the Ability Spec based on the passed in information and set a reference.
	if (FGameplayAbilitySpec* Spec = ActorInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle))
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get())
		{
			Spec->InputPressed = true;
			
			if (Spec->IsActive())
			{
				if (Spec->Ability.Get()->bReplicateInputDirectly && AbilitySystemComponent->IsOwnerActorAuthoritative() == false)
				{
					AbilitySystemComponent->ServerSetInputPressed(Spec->Ability.Get()->GetCurrentAbilitySpecHandle());
				}

				AbilitySystemComponent->AbilitySpecInputPressed(*Spec);

				// Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
				AbilitySystemComponent->InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec->Handle, Spec->ActivationInfo.GetActivationPredictionKey());
			}
			else
			{
				// Ability is not active, so try to activate it
				AbilitySystemComponent->TryActivateAbility(SpecHandle);
			}
		}
	}
}

void UTcGameplayAbility::HandleInputReleasedEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpecHandle SpecHandle)
{
	// Find the Ability Spec based on the passed in information and set a reference.
	if (FGameplayAbilitySpec* Spec = ActorInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle))
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get())
		{
			Spec->InputPressed = false;
			
			if (Spec && Spec->IsActive())
			{
				if (Spec->Ability.Get()->bReplicateInputDirectly && AbilitySystemComponent->IsOwnerActorAuthoritative() == false)
				{
					AbilitySystemComponent->ServerSetInputReleased(SpecHandle);
				}

				AbilitySystemComponent->AbilitySpecInputReleased(*Spec);

				// Invoke the InputReleased event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
				AbilitySystemComponent->InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, SpecHandle, Spec->ActivationInfo.GetActivationPredictionKey());
			}
		}
	}
}

void UTcGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	if (IsValid(ActorInfo->AvatarActor.Get()))
	{
		if (const APawn* AvatarPawn = Cast<APawn>(ActorInfo->AvatarActor.Get()))
		{
			if (const AController* PawnController = AvatarPawn->GetController())
			{
				if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PawnController->InputComponent.Get()))
				{
					// We need to clear the bindings from the Enhanced Input Component when the Ability is removed.
					EnhancedInputComponent->ClearBindingsForObject(Spec.Ability.Get());
				}
			}
		}
	}
	
	Super::OnRemoveAbility(ActorInfo, Spec);
}

