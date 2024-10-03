// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "TcPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ATcPlayerController();
	
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	//~Begin IGenericTeamAgentInterface
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override { MyTeamID = TeamID; }
	virtual FGenericTeamId GetGenericTeamId() const override { return MyTeamID; }
	//~End IGenericTeamAgentInterface
	
private:
	FGenericTeamId MyTeamID;
};
