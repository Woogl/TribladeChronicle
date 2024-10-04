// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TcAbilityTask_LookAtLocation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLookAtLocationFinished);

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API UTcAbilityTask_LookAtLocation : public UAbilityTask
{
	GENERATED_BODY()

public:
	UTcAbilityTask_LookAtLocation();
	
	UPROPERTY(BlueprintAssignable)
	FOnLookAtLocationFinished OnFinished;

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", Duration = "0.2", BlueprintInternalUseOnly = "TRUE"))
	static UTcAbilityTask_LookAtLocation* LookAtLocation(UGameplayAbility* OwningAbility, FVector TargetLocation, float Duration, bool bEaseIn, bool bEaseOut);

protected:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

private:
	UPROPERTY()
	float Duration;
	
	UPROPERTY()
	FVector TargetLocation;
	
	bool bEaseIn;
	bool bEaseOut;
	
	float StartTime;
	float EndTime;
};
