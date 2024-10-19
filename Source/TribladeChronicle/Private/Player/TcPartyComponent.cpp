// Copyright Woogle. All Rights Reserved.


#include "Player/TcPartyComponent.h"

#include "TcLogs.h"
#include "Character/TcHeroCharacter.h"
#include "Character/TcPartyData.h"
#include "Net/UnrealNetwork.h"
#include "Player/TcPlayerController.h"
#include "Player/TcPlayerState.h"

UTcPartyComponent::UTcPartyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTcPartyComponent::InitializePartySystem(UTcPartyData* InPartyData)
{
	OwningPlayerController = Cast<ATcPlayerController>(GetOwner());
	check(OwningPlayerController);

	OwningPawn = OwningPlayerController->GetPawn();
	check(OwningPawn);

	PartyData = InPartyData;

	Server_SpawnPartyMembers();
}

void UTcPartyComponent::Server_SpawnPartyMembers_Implementation()
{
	if (OwningPawn == nullptr)
	{
		return;
	}
	UWorld* World = OwningPawn->GetWorld();
	if (World && PartyData)
	{
		for (TSubclassOf<ATcHeroCharacter> MemberClass : PartyData->PartyMembers)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = OwningPlayerController;
			SpawnParams.Instigator = OwningPawn;
			ATcHeroCharacter* NewMember = World->SpawnActor<ATcHeroCharacter>(MemberClass, OwningPawn->GetActorTransform());
			
			PartyMembers.Add(NewMember);
		}
	}
	
	OwningPlayerController->Possess(PartyMembers[0]);
}

void UTcPartyComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PartyData);
	DOREPLIFETIME(ThisClass, PartyMembers);
	DOREPLIFETIME(ThisClass, OwningPlayerController);
	DOREPLIFETIME(ThisClass, OwningPawn);
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

void UTcPartyComponent::SetPartyMember(int32 MemberIndex, ATcCharacter* Character)
{
	PartyMembers.Reserve(MemberIndex);
	PartyMembers[MemberIndex] = Character;
}

void UTcPartyComponent::SwitchPartyMember(int32 MemberIndex)
{
	if (MemberIndex >= PartyMembers.Num() || MemberIndex < 0)
	{
		TC_ERROR(TEXT("Party member index %d is invalid."), MemberIndex);
	}
	
	ACharacter* NewCharacter = PartyMembers[MemberIndex];
	OwningPlayerController->Possess(NewCharacter);
}
