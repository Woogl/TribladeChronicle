// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TcPartyComponent.generated.h"


class ATcCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIBLADECHRONICLE_API UTcPartyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTcPartyComponent();

	UFUNCTION(BlueprintCallable)
	ATcCharacter* GetCurrentPartyMember() const;
	
	UFUNCTION(BlueprintCallable)
	ATcCharacter* GetNextPartyMember() const;

	UFUNCTION(BlueprintCallable)
	void SetPartyMember(int32 PartyMemberIndex, ATcCharacter* Character);

	UFUNCTION(BlueprintCallable)
	void SpawnPartyMembers();
	
private:
	UPROPERTY(Replicated)
	TArray<ATcCharacter*> PartyMembers;
};
