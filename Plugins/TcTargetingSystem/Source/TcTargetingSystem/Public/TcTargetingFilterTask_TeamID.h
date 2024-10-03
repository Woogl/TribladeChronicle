// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Tasks/TargetingFilterTask_BasicFilterTemplate.h"
#include "TcTargetingFilterTask_TeamID.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TCTARGETINGSYSTEM_API UTcTargetingFilterTask_TeamID : public UTargetingFilterTask_BasicFilterTemplate
{
	GENERATED_BODY()

public:
	virtual bool ShouldFilterTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const override;

protected:
	/** The set of required team IDs (must be one of these IDs to not be filtered out) */
	UPROPERTY(EditAnywhere, Category = "Targeting Filter | Class", Meta = (AllowAbstract=true))
	TSet<uint8> RequiredTeamIDs;

	/** The set of ignored team IDs (must NOT be one of these IDs) */
	UPROPERTY(EditAnywhere, Category = "Targeting Filter | Class", Meta = (AllowAbstract = true))
	TSet<uint8> IgnoredTeamIDs;

	/** Add source actor's team ID to "IgnoredTeamIDs" */
	UPROPERTY(EditAnywhere, Category = "Targeting Filter | Class", Meta = (AllowAbstract=true))
	bool bIgnoreSourceActorTeamID = true;

private:
	FGenericTeamId FindTeamID(AActor* TargetActor) const;
};
