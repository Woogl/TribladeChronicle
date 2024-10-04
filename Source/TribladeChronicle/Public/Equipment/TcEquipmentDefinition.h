// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TcEquipmentDefinition.generated.h"

class UTcEquipmentInstance;
class UTcAbilitySet;

USTRUCT()
struct FTcEquipmentActorToSpawn
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category=Equipment)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category=Equipment)
	FName AttachSocket;

	UPROPERTY(EditAnywhere, Category=Equipment)
	FTransform AttachTransform;
};

/**
 * 
 */
UCLASS(Blueprintable, Const, Abstract, BlueprintType)
class TRIBLADECHRONICLE_API UTcEquipmentDefinition : public UObject
{
	GENERATED_BODY()

public:
	// Class to spawn
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TSubclassOf<UTcEquipmentInstance> InstanceType;

	// Gameplay ability sets to grant when this is equipped
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TArray<TObjectPtr<const UTcAbilitySet>> AbilitySetsToGrant;

	// Actors to spawn on the pawn when this is equipped
	UPROPERTY(EditDefaultsOnly, Category=Equipment)
	TArray<FTcEquipmentActorToSpawn> ActorsToSpawn;
};
