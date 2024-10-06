// Copyright Woogle. All Rights Reserved.


#include "Character/TcCharacter.h"

#include "TcLogs.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/TcHealthSet.h"
#include "Character/TcHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/TcPlayerController.h"
#include "Player/TcPlayerState.h"

ATcCharacter::ATcCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetCapsuleComponent()->InitCapsuleSize(40.f, 90.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TcPawnCapsule"));

	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetCollisionProfileName(TEXT("TcPawnMesh"));

	GetCharacterMovement()->GravityScale = 1.0f;
	GetCharacterMovement()->MaxAcceleration = 2400.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
	GetCharacterMovement()->BrakingFriction = 6.0f;
	GetCharacterMovement()->GroundFriction = 8.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1400.0f;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->bAllowPhysicsRotationDuringAnimRootMotion = false;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = true;
	GetCharacterMovement()->SetCrouchedHalfHeight(65.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UTcAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	HealthComponent = CreateDefaultSubobject<UTcHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);

	HealthSet = CreateDefaultSubobject<UTcHealthSet>("HealthSet");

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;

	MyTeamID = FGenericTeamId::NoTeam;

	NetUpdateFrequency = 100.f;
}

void ATcCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, MyTeamID);
}

ATcPlayerController* ATcCharacter::GetTcPlayerController() const
{
	return CastChecked<ATcPlayerController>(Controller, ECastCheckedType::NullAllowed);
}

ATcPlayerState* ATcCharacter::GetTcPlayerState() const
{
	return CastChecked<ATcPlayerState>(GetPlayerState(), ECastCheckedType::NullAllowed);
}

UAbilitySystemComponent* ATcCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATcCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->GetOwnedGameplayTags(TagContainer);
	}
}

void ATcCharacter::ToggleCrouch()
{
	if (bIsCrouched || GetCharacterMovement()->bWantsToCrouch)
	{
		UnCrouch();
	}
	else if (GetCharacterMovement()->IsMovingOnGround())
	{
		Crouch();
	}
}

void ATcCharacter::OnAbilitySystemInitialized()
{
	UTcAbilitySystemComponent* TcASC = GetTcAbilitySystemComponent();
	check(TcASC);

	HealthComponent->InitializeWithAbilitySystem(TcASC);
}

void ATcCharacter::OnAbilitySystemUninitialized()
{
	HealthComponent->UninitializeFromAbilitySystem();
}

void ATcCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init ability actor info for the Server
	if (GetTcPlayerState())
	{
		GetTcAbilitySystemComponent()->InitializeAbilitySystem(PawnData, GetTcPlayerState());
	}
	else
	{
		GetTcAbilitySystemComponent()->InitializeAbilitySystem(PawnData, this);
	}
	OnAbilitySystemInitialized();
}

void ATcCharacter::UnPossessed()
{
	Super::UnPossessed();
}

void ATcCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	if (GetTcPlayerState())
	{
		GetTcAbilitySystemComponent()->InitializeAbilitySystem(PawnData, GetTcPlayerState());
	}
	else
	{
		GetTcAbilitySystemComponent()->InitializeAbilitySystem(PawnData, this);
	}
	OnAbilitySystemInitialized();
}

void ATcCharacter::OnDeathStarted(AActor* OwningActor)
{
	DisableMovementAndCollision();
}

void ATcCharacter::OnDeathFinished(AActor* OwningActor)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		DetachFromControllerPendingDestroy();
		SetLifeSpan(0.1f);
	}

	SetActorHiddenInGame(true);
}

void ATcCharacter::DisableMovementAndCollision()
{
	if (Controller)
	{
		Controller->SetIgnoreMoveInput(true);
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
}

void ATcCharacter::OnRep_MyTeamID(FGenericTeamId OldTeamID)
{
}

