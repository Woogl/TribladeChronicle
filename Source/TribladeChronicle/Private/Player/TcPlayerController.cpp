// Copyright Woogle. All Rights Reserved.


#include "Player/TcPlayerController.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Player/TcPlayerState.h"

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

