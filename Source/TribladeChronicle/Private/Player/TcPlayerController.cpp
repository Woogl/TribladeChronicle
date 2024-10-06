// Copyright Woogle. All Rights Reserved.


#include "Player/TcPlayerController.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Character/TcCharacter.h"

void ATcPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (ATcCharacter* TcCharacter = Cast<ATcCharacter>(GetPawn()))
	{
		if (UTcAbilitySystemComponent* TcASC = TcCharacter->GetTcAbilitySystemComponent())
		{
			TcASC->ProcessAbilityInput(DeltaTime, bGamePaused);
		}
	}
	
	Super::PostProcessInput(DeltaTime, bGamePaused);
}

