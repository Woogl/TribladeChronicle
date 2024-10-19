// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TcHeroAIController.generated.h"

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcHeroAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATcHeroAIController();

	//~Begin IGenericTeamAgentInterface interface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~End IGenericTeamAgentInterface interface
};
