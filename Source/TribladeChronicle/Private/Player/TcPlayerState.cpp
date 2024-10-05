// Copyright Woogle. All Rights Reserved.


#include "Player/TcPlayerState.h"

#include "TcLogs.h"
#include "AbilitySystem/TcAbilitySet.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/TcHealthSet.h"
#include "Net/UnrealNetwork.h"

ATcPlayerState::ATcPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTcAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	HealthSet = CreateDefaultSubobject<UTcHealthSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void ATcPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, PawnData, SharedParams);
}

UAbilitySystemComponent* ATcPlayerState::GetAbilitySystemComponent() const
{
	return GetTcAbilitySystemComponent();
}

void ATcPlayerState::SetPawnData(const UTcPawnData* InPawnData)
{
	check(InPawnData);

	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	if (PawnData)
	{
		UE_LOG(LogTc, Error, TEXT("Trying to set PawnData [%s] on player state [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(this), *GetNameSafe(PawnData));
		return;
	}
	
	PawnData = InPawnData;

	for (const UTcAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}

	ForceNetUpdate();
}

void ATcPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
}

void ATcPlayerState::OnRep_PawnData()
{
}
