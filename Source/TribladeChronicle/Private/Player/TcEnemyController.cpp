// Copyright Woogle. All Rights Reserved.


#include "Player/TcEnemyController.h"

ATcEnemyController::ATcEnemyController()
{
	bWantsPlayerState = true;
	bStopAILogicOnUnposses = false;

	// 0 for player, 1 for enemy
	SetGenericTeamId(1);
}

ETeamAttitude::Type ATcEnemyController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// if (const APawn* OtherPawn = Cast<APawn>(&Other))
	// {
	// 	if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
	// 	{
	// 		return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
	// 	}
	// }
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();

			//Checking Other pawn ID to define Attitude
			if (OtherTeamID.GetId() != GetGenericTeamId().GetId())
			{
				return ETeamAttitude::Hostile;
			}
			else
			{
				return ETeamAttitude::Friendly;
			}
		}
	}

	return ETeamAttitude::Neutral;
}
