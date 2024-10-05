// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TcAbilityTask_LookAtLocation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLookAtLocationFinished);

/**
 * The source actor adjust rotation to face the target location.
 */
UCLASS()
class TRIBLADECHRONICLE_API UTcAbilityTask_LookAtLocation : public UAbilityTask
{
	GENERATED_BODY()

public:
	UTcAbilityTask_LookAtLocation();
	
	UPROPERTY(BlueprintAssignable)
	FOnLookAtLocationFinished OnFinished;

	virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", Duration = "0.2", BlueprintInternalUseOnly = "TRUE"))
	static UTcAbilityTask_LookAtLocation* LookAtLocation(UGameplayAbility* OwningAbility, FVector TargetLocation, float Duration, bool bEaseIn, bool bEaseOut);

protected:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

private:
	UPROPERTY(Replicated)
	float Duration;
	
	UPROPERTY(Replicated)
	FVector TargetLocation;
	
	bool bEaseIn;
	bool bEaseOut;
	
	float StartTime;
	float EndTime;
};
