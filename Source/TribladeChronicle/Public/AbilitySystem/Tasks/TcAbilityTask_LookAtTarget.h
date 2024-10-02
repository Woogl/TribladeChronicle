// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TcAbilityTask_LookAtTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLookAtTargetFinished);

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API UTcAbilityTask_LookAtTarget : public UAbilityTask
{
	GENERATED_BODY()

public:
	UTcAbilityTask_LookAtTarget();
	
	UPROPERTY(BlueprintAssignable)
	FOnLookAtTargetFinished OnFinished;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UTcAbilityTask_LookAtTarget* LookAtTarget(UGameplayAbility* OwningAbility, AActor* TargetActor, float Duration = 0.2f, bool EaseIn, bool EaseOut);

protected:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

private:
	UPROPERTY()
	float Duration;
	
	UPROPERTY()
	AActor* TargetActor;
	
	bool bEaseIn;
	bool bEaseOut;
	
	float StartTime;
	float EndTime;
};
