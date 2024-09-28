// Copyright Woogle. All Rights Reserved.


#include "GameMode/TcGameMode.h"

#include "Character/TcCharacter.h"
#include "Player/TcPlayerController.h"
#include "Player/TcPlayerState.h"

ATcGameMode::ATcGameMode()
{
	PlayerControllerClass = ATcPlayerController::StaticClass();
	PlayerStateClass = ATcPlayerState::StaticClass();
	DefaultPawnClass = ATcCharacter::StaticClass();
}
