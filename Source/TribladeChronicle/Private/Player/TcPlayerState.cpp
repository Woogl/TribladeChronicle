// Copyright Woogle. All Rights Reserved.


#include "Player/TcPlayerState.h"

#include "TcLogs.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/TcHealthSet.h"
#include "Net/UnrealNetwork.h"
#include "Player/TcPartyComponent.h"

ATcPlayerState::ATcPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTcAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	PartyComponent = CreateDefaultSubobject<UTcPartyComponent>(TEXT("PartyComponent"));
	PartyComponent->SetIsReplicated(true);

	HealthSet = CreateDefaultSubobject<UTcHealthSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

// void ATcPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//     
// 	FDoRepLifetimeParams SharedParams;
// 	SharedParams.bIsPushBased = true;
//
// 	DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, PawnData, SharedParams);
// }

UAbilitySystemComponent* ATcPlayerState::GetAbilitySystemComponent() const
{
	return GetTcAbilitySystemComponent();
}

void ATcPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
    
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
}
