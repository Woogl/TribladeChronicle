// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "TcPlayerState.generated.h"

class UTcPartyComponent;
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

	virtual void PostInitializeComponents() override;

protected:
    
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTcAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTcPartyComponent> PartyComponent;

	// Health attribute set used by this actor.
	UPROPERTY()
	TObjectPtr<const UTcHealthSet> HealthSet;
};