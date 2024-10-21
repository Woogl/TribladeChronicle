// Copyright Woogle. All Rights Reserved.


#include "AbilitySystem/TcAbilitySystemComponent.h"

#include "TcLogs.h"
#include "AbilitySystem/TcAbilitySet.h"
#include "AbilitySystem/Abilities/TcGameplayAbility.h"
#include "Character/TcPawnData.h"

UTcAbilitySystemComponent::UTcAbilitySystemComponent()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void UTcAbilitySystemComponent::InitializeAbilitySystem(UTcPawnData* InPawnData, AActor* InOwnerActor, AActor* InAvatarActor)
{
	check(InOwnerActor);
	check(InAvatarActor);
	
	// Clean up the old ability system component.
	UninitializeAbilitySystem();

	AActor* ExistingAvatar = GetAvatarActor();

	UE_LOG(LogTc, Verbose, TEXT("Setting up ASC [%s] on pawn [%s] owner [%s], existing [%s] "), *GetNameSafe(this), *GetNameSafe(InAvatarActor), *GetNameSafe(InOwnerActor), *GetNameSafe(ExistingAvatar));

	if ((ExistingAvatar != nullptr) && (ExistingAvatar != InAvatarActor))
	{
		UE_LOG(LogTc, Log, TEXT("Existing avatar (authority=%d)"), ExistingAvatar->HasAuthority() ? 1 : 0);
	}

	InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	check(InPawnData);

	if (InOwnerActor->GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	
	if (InPawnData)
	{
		for (const UTcAbilitySet* AbilitySet : InPawnData->AbilitySets)
		{
			if (AbilitySet)
			{
				AbilitySet->GiveToAbilitySystem(this, nullptr);
			}
		}
	}

	InAvatarActor->ForceNetUpdate();

	OnAbilitySystemInitialized.Broadcast();
}

void UTcAbilitySystemComponent::UninitializeAbilitySystem()
{
	// Uninitialize the ASC if we're still the avatar actor (otherwise another pawn already did it when they became the avatar actor)
	if (GetAvatarActor() == GetOwner())
	{
		CancelAbilities();
		ClearAbilityInput();
		RemoveAllGameplayCues();

		if (GetOwnerActor() != nullptr)
		{
			SetAvatarActor(nullptr);
		}
		else
		{
			// If the ASC doesn't have a valid owner, we need to clear *all* actor info, not just the avatar pairing
			ClearActorInfo();
		}

		OnAbilitySystemUninitialized.Broadcast();
	}
}

void UTcAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
			{
				InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UTcAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
			{
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}

void UTcAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();
	
	// for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	// {
	// 	if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
	// 	{
	// 		if (AbilitySpec->Ability && !AbilitySpec->IsActive())
	// 		{
	// 			const UTcGameplayAbility* Tcbility = CastChecked<UTcGameplayAbility>(AbilitySpec->Ability);
	//
	// 			if (Tcbility->GetActivationPolicy() == ETcAbilityActivationPolicy::WhileInputActive)
	// 			{
	// 				AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
	// 			}
	// 		}
	// 	}
	// }

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;

				if (AbilitySpec->IsActive())
				{
					AbilitySpecInputPressed(*AbilitySpec);
				}
				else
				{
					const UTcGameplayAbility* TcAbility = CastChecked<UTcGameplayAbility>(AbilitySpec->Ability);

					// if (TcAbility->GetActivationPolicy() == ETcAbilityActivationPolicy::OnInputTriggered)
					// {
						AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
					//}
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		TryActivateAbility(AbilitySpecHandle);
	}
	
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;

				if (AbilitySpec->IsActive())
				{
					AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}

	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UTcAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void UTcAbilitySystemComponent::OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate)
{
	if (!OnAbilitySystemInitialized.IsBoundToObject(Delegate.GetUObject()))
	{
		OnAbilitySystemInitialized.Add(Delegate);
	}
	
	Delegate.Execute();
}

void UTcAbilitySystemComponent::OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate Delegate)
{
	if (!OnAbilitySystemUninitialized.IsBoundToObject(Delegate.GetUObject()))
	{
		OnAbilitySystemUninitialized.Add(Delegate);
	}
}

void UTcAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);
	
	if (Spec.IsActive())
	{
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
	}
}

void UTcAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);

	if (Spec.IsActive())
	{
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
	}
}
