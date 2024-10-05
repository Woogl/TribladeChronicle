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

protected:
	virtual void BeginPlay() override;
};
