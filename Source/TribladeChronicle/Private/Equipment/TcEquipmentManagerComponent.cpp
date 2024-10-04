// Copyright Woogle. All Rights Reserved.


#include "Equipment/TcEquipmentManagerComponent.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/TcAbilitySet.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Equipment/TcEquipmentDefinition.h"
#include "Equipment/TcEquipmentInstance.h"
#include "Net/UnrealNetwork.h"

UTcEquipmentInstance* FTcEquipmentList::AddEntry(TSubclassOf<UTcEquipmentDefinition> EquipmentDefinition)
{
	UTcEquipmentInstance* Result = nullptr;

	check(EquipmentDefinition != nullptr);
	check(OwnerComponent);
	check(OwnerComponent->GetOwner()->HasAuthority());
	
	const UTcEquipmentDefinition* EquipmentCDO = GetDefault<UTcEquipmentDefinition>(EquipmentDefinition);

	TSubclassOf<UTcEquipmentInstance> InstanceType = EquipmentCDO->InstanceType;
	if (InstanceType == nullptr)
	{
		InstanceType = UTcEquipmentInstance::StaticClass();
	}
	
	FTcAppliedEquipmentEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.EquipmentDefinition = EquipmentDefinition;
	NewEntry.Instance = NewObject<UTcEquipmentInstance>(OwnerComponent->GetOwner(), InstanceType);  //@TODO: Using the actor instead of component as the outer due to UE-127172
	Result = NewEntry.Instance;

	if (UTcAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		for (const TObjectPtr<const UTcAbilitySet>& AbilitySet : EquipmentCDO->AbilitySetsToGrant)
		{
			AbilitySet->GiveToAbilitySystem(ASC, Result);
		}
	}
	else
	{
		//@TODO: Warning logging?
	}

	Result->SpawnEquipmentActors(EquipmentCDO->ActorsToSpawn);

	return Result;
}

void FTcEquipmentList::RemoveEntry(UTcEquipmentInstance* Instance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FTcAppliedEquipmentEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		{
			if (UTcAbilitySystemComponent* ASC = GetAbilitySystemComponent())
			{
				// ASC->ClearAbility();
				// Entry.GrantedHandles.TakeFromAbilitySystem(ASC);
			}

			Instance->DestroyEquipmentActors();
			
			EntryIt.RemoveCurrent();
		}
	}
}

UTcAbilitySystemComponent* FTcEquipmentList::GetAbilitySystemComponent() const
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	return Cast<UTcAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor));
}

UTcEquipmentManagerComponent::UTcEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, EquipmentList(this)
{
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
}

void UTcEquipmentManagerComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, EquipmentList);
}

UTcEquipmentInstance* UTcEquipmentManagerComponent::EquipItem(TSubclassOf<UTcEquipmentDefinition> EquipmentDefinition)
{
	UTcEquipmentInstance* Result = nullptr;
	if (EquipmentDefinition != nullptr)
	{
		Result = EquipmentList.AddEntry(EquipmentDefinition);
		if (Result != nullptr)
		{
			Result->OnEquipped();
		
			if (IsUsingRegisteredSubObjectList() && IsReadyForReplication())
			{
				AddReplicatedSubObject(Result);
			}
		}
	}
	return Result;
}

void UTcEquipmentManagerComponent::UnequipItem(UTcEquipmentInstance* ItemInstance)
{
}
