// Copyright Woogle. All Rights Reserved.


#include "Player/TcPlayerState.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/TcHealthSet.h"

ATcPlayerState::ATcPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTcAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	HealthSet = CreateDefaultSubobject<UTcHealthSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ATcPlayerState::GetAbilitySystemComponent() const
{
	return GetTcAbilitySystemComponent();
}
