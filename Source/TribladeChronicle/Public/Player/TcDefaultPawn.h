// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TcDefaultPawn.generated.h"

class UTcPartyData;

UCLASS()
class TRIBLADECHRONICLE_API ATcDefaultPawn : public APawn
{
	GENERATED_BODY()

public:
	ATcDefaultPawn();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "TC|Pawn Data", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTcPartyData> PartyData;
};
