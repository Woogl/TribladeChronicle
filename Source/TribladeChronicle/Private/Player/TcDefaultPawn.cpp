// Copyright Woogle. All Rights Reserved.


#include "Player/TcDefaultPawn.h"

#include "Player/TcPartyComponent.h"
#include "Player/TcPlayerController.h"

ATcDefaultPawn::ATcDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// I don't use it as a player character
	InitialLifeSpan = 10.f;
}

void ATcDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (ATcPlayerController* TcPlayerController = GetController<ATcPlayerController>())
	{
		if (UTcPartyComponent* PartyComponent = TcPlayerController->GetPartyComponent())
		{
			PartyComponent->Server_RequestInitializePartySystem();
		}
	}
}

