// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "TcPlayerController.generated.h"

class UTcPartyComponent;
/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API ATcPlayerController : public ACommonPlayerController
{
	GENERATED_BODY()
	
public:
	ATcPlayerController();
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	UFUNCTION(BlueprintCallable)
	UTcPartyComponent* GetPartyComponent() { return PartyComponent; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTcPartyComponent> PartyComponent;
};
