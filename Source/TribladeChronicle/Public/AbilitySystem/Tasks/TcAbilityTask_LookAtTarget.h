// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TcAbilityTask_LookAtTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLookAtTargetFinished);

/**
 *  * The source actor adjust rotation to face the target actor.
 */
UCLASS()
class TRIBLADECHRONICLE_API UTcAbilityTask_LookAtTarget : public UAbilityTask
{
	GENERATED_BODY()

public:
	UTcAbilityTask_LookAtTarget();
	
	UPROPERTY(BlueprintAssignable)
	FOnLookAtTargetFinished OnFinished;

	virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", Duration = "0.2", BlueprintInternalUseOnly = "TRUE"))
	static UTcAbilityTask_LookAtTarget* LookAtTarget(UGameplayAbility* OwningAbility, AActor* TargetActor, float Duration, bool bEaseIn, bool bEaseOut);

protected:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

private:
	UPROPERTY(Replicated)
	float Duration;
	
	UPROPERTY(Replicated)
	AActor* TargetActor;
	
	bool bEaseIn;
	bool bEaseOut;
	
	float StartTime;
	float EndTime;
};
