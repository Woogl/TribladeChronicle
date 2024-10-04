// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "TcEquipmentManagerComponent.generated.h"

class UTcEquipmentInstance;
class UTcEquipmentDefinition;
class UTcAbilitySystemComponent;

/** A single piece of applied equipment */
USTRUCT(BlueprintType)
struct FTcAppliedEquipmentEntry
{
	GENERATED_BODY()

	FString GetDebugString() const;

private:
	friend FTcEquipmentList;
	friend UTcEquipmentManagerComponent;

	// The equipment class that got equipped
	UPROPERTY()
	TSubclassOf<UTcEquipmentDefinition> EquipmentDefinition;

	UPROPERTY()
	TObjectPtr<UTcEquipmentInstance> Instance = nullptr;
};

/** List of applied equipment */
USTRUCT(BlueprintType)
struct FTcEquipmentList
{
	GENERATED_BODY()

	FTcEquipmentList()
		: OwnerComponent(nullptr)
	{
	}

	FTcEquipmentList(UActorComponent* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}

public:
	UTcEquipmentInstance* AddEntry(TSubclassOf<UTcEquipmentDefinition> EquipmentDefinition);
	void RemoveEntry(UTcEquipmentInstance* Instance);

private:
	UTcAbilitySystemComponent* GetAbilitySystemComponent() const;

	friend UTcEquipmentManagerComponent;

private:
	// Replicated list of equipment entries
	UPROPERTY()
	TArray<FTcAppliedEquipmentEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

/**
 * 
 */
UCLASS(BlueprintType, Const)
class TRIBLADECHRONICLE_API UTcEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UTcEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	UTcEquipmentInstance* EquipItem(TSubclassOf<UTcEquipmentDefinition> EquipmentDefinition);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void UnequipItem(UTcEquipmentInstance* ItemInstance);

private:
	UPROPERTY(Replicated)
	FTcEquipmentList EquipmentList;
};
