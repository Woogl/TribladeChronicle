// Copyright Woogle. All Rights Reserved.


#include "Player/TcPlayerController.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Player/TcPlayerState.h"

void ATcPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);
	
	if (ATcPlayerState* PState = GetPlayerState<ATcPlayerState>())
	{
		if (UTcAbilitySystemComponent* TcASC = PState->GetTcAbilitySystemComponent())
		{
			TcASC->ProcessAbilityInput(DeltaTime, bGamePaused);
		}
	}
	
	Super::PostProcessInput(DeltaTime, bGamePaused);
}
