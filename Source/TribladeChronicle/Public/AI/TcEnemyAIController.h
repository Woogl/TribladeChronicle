// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TcEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATcEnemyAIController();

	//~Begin IGenericTeamAgentInterface interface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~End IGenericTeamAgentInterface interface
};
