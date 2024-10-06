// Copyright Woogle. All Rights Reserved.


#include "Character/TcEnemyCharacter.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"

ATcEnemyCharacter::ATcEnemyCharacter()
{
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void ATcEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 0 for player team, 1 for enemy team
	SetGenericTeamId(1);
}
