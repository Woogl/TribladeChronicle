// Copyright Woogle. All Rights Reserved.


#include "Character/TcEnemyCharacter.h"

#include "AbilitySystem/TcAbilitySet.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Character/TcHealthComponent.h"

ATcEnemyCharacter::ATcEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTcAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void ATcEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeAbilitySystem();

	if (AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(GetAbilitySystemComponent(), this);
	}
}

void ATcEnemyCharacter::InitializeAbilitySystem()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent);
}
