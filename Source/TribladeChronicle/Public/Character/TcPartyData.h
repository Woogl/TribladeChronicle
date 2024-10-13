// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TcPartyData.generated.h"

class ATcHeroCharacter;
/**
 * 
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "TC Party Data", ShortTooltip = "Data asset used to define a Party."))
class TRIBLADECHRONICLE_API UTcPartyData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TC|Party")
	TArray<TSubclassOf<ATcHeroCharacter>> PartyMembers;
};
