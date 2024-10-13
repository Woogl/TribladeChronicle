// Copyright Woogle. All Rights Reserved.


#include "Player/TcPartyComponent.h"

#include "Character/TcHeroCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Player/TcPlayerState.h"

UTcPartyComponent::UTcPartyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTcPartyComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PartyMembers);
}

ATcCharacter* UTcPartyComponent::GetCurrentPartyMember() const
{
	if (ATcPlayerState* TcPS = Cast<ATcPlayerState>(GetOwner()))
	{
		if (APawn* Pawn = TcPS->GetPawn())
		{
			return Cast<ATcCharacter>(Pawn);
		}
	}
	return nullptr;
}

ATcCharacter* UTcPartyComponent::GetNextPartyMember() const
{
	int32 CurrentPartyMemberIndex = PartyMembers.IndexOfByKey(GetCurrentPartyMember());
	int32 NextPartyMemberIndex = (CurrentPartyMemberIndex + 1) % PartyMembers.Num();
	return PartyMembers[NextPartyMemberIndex];
}

void UTcPartyComponent::SetPartyMember(int32 PartyMemberIndex, ATcCharacter* Character)
{
	PartyMembers.Reserve(PartyMemberIndex);
	PartyMembers[PartyMemberIndex] = Character;
}

void UTcPartyComponent::SpawnPartyMembers()
{
	UWorld* World = GetWorld();
	check(World);
	
	for (ATcCharacter* PartyMember : PartyMembers)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//World->SpawnActor(PartyMember->StaticClass, GetCurrentPartyMember()->GetTransform());
	}
}
