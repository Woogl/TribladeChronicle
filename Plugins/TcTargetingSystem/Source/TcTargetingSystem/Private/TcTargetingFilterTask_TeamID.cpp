// Copyright Woogle. All Rights Reserved.


#include "TcTargetingFilterTask_TeamID.h"

#include "GenericTeamAgentInterface.h"

bool UTcTargetingFilterTask_TeamID::ShouldFilterTarget(const FTargetingRequestHandle& TargetingHandle, const FTargetingDefaultResultData& TargetData) const
{
	FGenericTeamId TargetActorTeamID = FGenericTeamId::NoTeam;
	if (AActor* TargetActor = TargetData.HitResult.GetActor())
	{
		TargetActorTeamID = FindTeamID(TargetActor);
	}

	FGenericTeamId SourceActorTeamID = FGenericTeamId::NoTeam;
	if (const FTargetingSourceContext* SourceContext = FTargetingSourceContext::Find(TargetingHandle))
	{
		if (SourceContext->SourceActor)
		{
			SourceActorTeamID = FindTeamID(SourceContext->SourceActor);
		}
	}
	
	if (AActor* TargetActor = TargetData.HitResult.GetActor())
	{
		// if the target is one of these IDs, filter it out
		for (uint8 IDFilter : IgnoredTeamIDs)
		{
			if (IDFilter == TargetActorTeamID)
			{
				return true;
			}
		}

		// if the target is one of these IDs, do not filter it out
		for (uint8 IDFilter : RequiredTeamIDs)
		{
			if (IDFilter == TargetActorTeamID)
			{
				return false;
			}
		}

		if (bIgnoreSourceActorTeamID)
		{
			if (SourceActorTeamID == TargetActorTeamID)
			{
				return true;
			}
		}

		// if we do not have required class IDs, we do NOT want to filter this target
		return (RequiredTeamIDs.Num() > 0);
	}

	return true;
}

FGenericTeamId UTcTargetingFilterTask_TeamID::FindTeamID(AActor* TargetActor) const
{
	if (APawn* Pawn = Cast<APawn>(TargetActor))
	{
		if (AController* Controller = Pawn->GetController())
		{
			if (IGenericTeamAgentInterface* Interface = Cast<IGenericTeamAgentInterface>(Controller))
			{
				return Interface->GetGenericTeamId();
			}
		}
	}
	return FGenericTeamId::NoTeam;
}
