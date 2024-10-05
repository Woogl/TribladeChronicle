// Copyright Woogle. All Rights Reserved.


#include "Character/TcEnemyCharacter.h"

ATcEnemyCharacter::ATcEnemyCharacter()
{
}

void ATcEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 0 for player team, 1 for enemy team
	SetGenericTeamId(1);
}
