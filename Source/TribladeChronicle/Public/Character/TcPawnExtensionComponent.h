// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "TcPawnExtensionComponent.generated.h"

class UTcPawnData;
class UTcAbilitySystemComponent;

UCLASS()
class TRIBLADECHRONICLE_API UTcPawnExtensionComponent : public UPawnComponent
{
	GENERATED_BODY()

public:	
	UTcPawnExtensionComponent(const FObjectInitializer& ObjectInitializer);

	/** Returns the pawn extension component if one exists on the specified actor. */
	UFUNCTION(BlueprintPure, Category = "TC|Pawn")
	static UTcPawnExtensionComponent* FindPawnExtensionComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UTcPawnExtensionComponent>() : nullptr); }

	const UTcPawnData* GetPawnData() const { return PawnData; }

	/** Sets the current pawn data */
	void SetPawnData(const UTcPawnData* InPawnData);

	/** Gets the current ability system component, which may be owned by a different actor */
	UFUNCTION(BlueprintPure, Category = "TC|Pawn")
	UTcAbilitySystemComponent* GetTcAbilitySystemComponent() const;

	/** Should be called by the owning pawn to become the avatar of the ability system. */
	void InitializeAbilitySystem(UTcAbilitySystemComponent* InASC, AActor* InOwnerActor);

	/** Should be called by the owning pawn to remove itself as the avatar of the ability system. */
	void UninitializeAbilitySystem();

	/** Register with the OnAbilitySystemInitialized delegate and broadcast if our pawn has been registered with the ability system component */
	void OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate Delegate);

	/** Register with the OnAbilitySystemUninitialized delegate fired when our pawn is removed as the ability system's avatar actor */
	void OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate Delegate);
	
protected:
	virtual void OnRegister() override;
	
	UFUNCTION()
	void OnRep_PawnData();

	/** Delegate fired when our pawn becomes the ability system's avatar actor */
	FSimpleMulticastDelegate OnAbilitySystemInitialized;

	/** Delegate fired when our pawn is removed as the ability system's avatar actor */
	FSimpleMulticastDelegate OnAbilitySystemUninitialized;
	
	/** Pawn data used to create the pawn. Specified from a spawn function or on a placed instance. */
	UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_PawnData, Category = "TC|Pawn")
	TObjectPtr<const UTcPawnData> PawnData;

	/** Pointer to the ability system component that is cached for convenience. */
	UPROPERTY(Transient)
	TObjectPtr<UTcAbilitySystemComponent> AbilitySystemComponent;
};
