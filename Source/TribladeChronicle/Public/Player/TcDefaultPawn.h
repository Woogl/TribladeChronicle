// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TcDefaultPawn.generated.h"

class UTcPartyData;

/**
 * TcGameMode use it as a default pawn class.
 * But it's only used for player initialization process.
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcDefaultPawn : public APawn
{
	GENERATED_BODY()

public:
	ATcDefaultPawn();

protected:
	virtual void BeginPlay() override;
};
