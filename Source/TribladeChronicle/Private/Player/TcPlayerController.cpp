// Copyright Woogle. All Rights Reserved.


#include "Player/TcPlayerController.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Player/TcPlayerState.h"

ATcPlayerController::ATcPlayerController()
{
	// 0 for player, 1 for enemy
	SetGenericTeamId(0);
}

void ATcPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (ATcPlayerState* TcPS = GetPlayerState<ATcPlayerState>())
	{
		if (UTcAbilitySystemComponent* TcASC = TcPS->GetTcAbilitySystemComponent())
		{
			TcASC->ProcessAbilityInput(DeltaTime, bGamePaused);
		}
	}
	
	Super::PostProcessInput(DeltaTime, bGamePaused);
}

