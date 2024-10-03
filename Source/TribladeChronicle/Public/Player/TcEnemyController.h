// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TcEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	ATcEnemyController();

	//~Begin IGenericTeamAgentInterface interface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~End IGenericTeamAgentInterface interface

private:
};
