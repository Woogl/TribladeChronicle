// Copyright Woogle. All Rights Reserved.


#include "Character/TcEnemyCharacter.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"

ATcEnemyCharacter::ATcEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTcAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void ATcEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Init ability enemy actor info
	GetTcAbilitySystemComponent()->InitializeAbilitySystem(PawnData, this, this);
}

UAbilitySystemComponent* ATcEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATcEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 0 for player team, 1 for enemy team
	SetGenericTeamId(1);
}
