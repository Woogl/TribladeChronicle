// Copyright Woogle. All Rights Reserved.


#include "Player/TcPlayerController.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Character/TcCharacter.h"
#include "Player/TcPartyComponent.h"

ATcPlayerController::ATcPlayerController()
{
	PartyComponent = CreateDefaultSubobject<UTcPartyComponent>(TEXT("PartyComponent"));
	PartyComponent->SetIsReplicated(true);
}

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

