// Copyright Woogle. All Rights Reserved.


#include "Player/TcPlayerState.h"

#include "TcLogs.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/TcHealthSet.h"
#include "Net/UnrealNetwork.h"

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

void ATcPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
    
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
}
