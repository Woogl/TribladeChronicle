// Copyright Woogle. All Rights Reserved.


#include "Player/TcDefaultPawn.h"

#include "Net/UnrealNetwork.h"
#include "Player/TcPartyComponent.h"
#include "Player/TcPlayerController.h"

ATcDefaultPawn::ATcDefaultPawn()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATcDefaultPawn::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PartyData);
}

void ATcDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (ATcPlayerController* TcPlayerController = GetController<ATcPlayerController>())
	{
		if (UTcPartyComponent* PartyComponent = TcPlayerController->GetPartyComponent())
		{
			PartyComponent->InitializePartySystem(PartyData);
		}
	}
}

