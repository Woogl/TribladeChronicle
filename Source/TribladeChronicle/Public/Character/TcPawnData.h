// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TcPawnData.generated.h"

class UTcAbilitySet;
class UTcInputConfig;

/**
 * Non-mutable data asset that contains properties used to define a pawn.
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "TC Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class TRIBLADECHRONICLE_API UTcPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TC|Abilities")
	TArray<TObjectPtr<UTcAbilitySet>> AbilitySets;

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TC|Input")
	TObjectPtr<UTcInputConfig> InputConfig;
};
