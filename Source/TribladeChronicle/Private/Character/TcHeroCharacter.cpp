// Copyright Woogle. All Rights Reserved.


#include "Character/TcHeroCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "TcGameplayTags.h"
#include "AbilitySystem/TcAbilitySet.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/TcPawnData.h"
#include "Equipment/TcEquipmentManagerComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/TcInputComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/TcPlayerState.h"

ATcHeroCharacter::ATcHeroCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	EquipmentManagerComponent = CreateDefaultSubobject<UTcEquipmentManagerComponent>(TEXT("EquipmentManagerComponent"));

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AutoPossessAI = EAutoPossessAI::Spawned;
}

// void ATcHeroCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
// 	
// }

void ATcHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UTcInputComponent* TcInputComp = Cast<UTcInputComponent>(PlayerInputComponent))
	{
		TcInputComp->BindAbilityActions(PawnData->InputConfig, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
		
		TcInputComp->BindNativeAction(PawnData->InputConfig, TcGameplayTags::INPUT_MOVE, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
		TcInputComp->BindNativeAction(PawnData->InputConfig, TcGameplayTags::INPUT_LOOK, ETriggerEvent::Triggered, this, &ThisClass::Input_Look, false);
	}
}

void ATcHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 0 for player team, 1 for enemy team
	SetGenericTeamId(0);
}

void ATcHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	GetTcAbilitySystemComponent()->InitializeAbilitySystem(PawnData, GetPlayerState(), this);
}

void ATcHeroCharacter::UnPossessed()
{
	Super::UnPossessed();
	GetMovementComponent()->StopMovementImmediately();
}

void ATcHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	if (GetPlayerState()) // PlayerState can be null during unpossessing.
	{
		GetTcAbilitySystemComponent()->InitializeAbilitySystem(PawnData, GetPlayerState(), this);
	}
}

void ATcHeroCharacter::FinishDestroy()
{
	Super::FinishDestroy();

	if (GetPlayerState())
	{
		GetPlayerState()->Destroy();
	}
}

void ATcHeroCharacter::Input_Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATcHeroCharacter::Input_Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATcHeroCharacter::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	GetTcAbilitySystemComponent()->AbilityInputTagPressed(InputTag);
}

void ATcHeroCharacter::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	GetTcAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
}
