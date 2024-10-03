// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/TcPawnData.h"
#include "GameFramework/PlayerState.h"
#include "TcPlayerState.generated.h"

class UTcAbilitySystemComponent;
class UAbilitySystemComponent;
class UTcHealthSet;

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATcPlayerState();

	UFUNCTION(BlueprintCallable, Category = "TC|PlayerState")
	UTcAbilitySystemComponent* GetTcAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	const UTcPawnData* GetPawnData() const { return PawnData; }
	void SetPawnData(const UTcPawnData* InPawnData);

	virtual void PostInitializeComponents() override;

protected:
	UFUNCTION()
	void OnRep_PawnData();
	
	UPROPERTY(ReplicatedUsing = OnRep_PawnData)
	TObjectPtr<const UTcPawnData> PawnData;
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTcAbilitySystemComponent> AbilitySystemComponent;

	// Health attribute set used by this actor.
	UPROPERTY()
	TObjectPtr<const UTcHealthSet> HealthSet;
};
