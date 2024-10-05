// Copyright Woogle. All Rights Reserved.


#include "Character/TcCharacter.h"

#include "TcLogs.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Character/TcHealthComponent.h"
#include "Character/TcPawnExtensionComponent.h"
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

	PawnExtComponent = CreateDefaultSubobject<UTcPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	PawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemInitialized));
	PawnExtComponent->OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemUninitialized));

	HealthComponent = CreateDefaultSubobject<UTcHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;

	MyTeamID = FGenericTeamId::NoTeam;
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

UTcAbilitySystemComponent* ATcCharacter::GetTcAbilitySystemComponent() const
{
	return Cast<UTcAbilitySystemComponent>(GetAbilitySystemComponent());
}

UAbilitySystemComponent* ATcCharacter::GetAbilitySystemComponent() const
{
	if (PawnExtComponent == nullptr)
	{
		return nullptr;
	}

	return PawnExtComponent->GetTcAbilitySystemComponent();
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

	PawnExtComponent->HandleControllerChanged();
	
	// Init ability actor info for the Server
	PawnExtComponent->SetPawnData(PawnData);
	PawnExtComponent->InitializeAbilitySystem(GetTcAbilitySystemComponent(), GetTcPlayerState());
}

void ATcCharacter::UnPossessed()
{
	Super::UnPossessed();

	PawnExtComponent->HandleControllerChanged();
}

void ATcCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();

	PawnExtComponent->HandleControllerChanged();
}

void ATcCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	PawnExtComponent->SetPawnData(PawnData);
	PawnExtComponent->InitializeAbilitySystem(GetTcAbilitySystemComponent(), GetTcPlayerState());
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

