// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TcPlayerState.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/TcHealthSet.h"

ATcPlayerState::ATcPlayerState()
{
	NetUpdateFrequency = 100.f;
	
	AbilitySystemComponent = CreateDefaultSubobject<UTcAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	HealthSet = CreateDefaultSubobject<UTcHealthSet>("AttributeSet");
}

UAbilitySystemComponent* ATcPlayerState::GetAbilitySystemComponent() const
{
	return GetTcAbilitySystemComponent();
}
