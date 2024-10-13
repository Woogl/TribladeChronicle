// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/TcCharacter.h"
#include "TcEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcEnemyCharacter : public ATcCharacter
{
	GENERATED_BODY()
	
public:
	ATcEnemyCharacter();
	virtual void PostInitializeComponents() override;

protected:
	// Enemy characters has ASC in the Character. Hero characters has ASC in the PlayerState.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TC|Ability", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTcAbilitySystemComponent> AbilitySystemComponent;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
};
