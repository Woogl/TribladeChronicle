// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TcPartyComponent.generated.h"


class ATcPlayerController;
class UTcPartyData;
class ATcCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIBLADECHRONICLE_API UTcPartyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTcPartyComponent();

	void InitializePartySystem(UTcPartyData* InPartyData);
	
	UFUNCTION(BlueprintCallable)
	ATcCharacter* GetCurrentPartyMember() const;
	
	UFUNCTION(BlueprintCallable)
	ATcCharacter* GetNextPartyMember() const;

	UFUNCTION(BlueprintCallable)
	void SetPartyMember(int32 MemberIndex, ATcCharacter* Character);

	UFUNCTION(BlueprintCallable)
	void SwitchPartyMember(int32 MemberIndex);
	
private:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SpawnPartyMembers();
	
	UPROPERTY(Replicated)
	TObjectPtr<UTcPartyData> PartyData;
	
	UPROPERTY(Replicated)
	TArray<ATcCharacter*> PartyMembers;

	UPROPERTY(Replicated)
	ATcPlayerController* OwningPlayerController;

	UPROPERTY(Replicated)
	APawn* OwningPawn;
};
