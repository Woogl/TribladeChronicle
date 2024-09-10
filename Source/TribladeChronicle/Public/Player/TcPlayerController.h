// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TcPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
};
