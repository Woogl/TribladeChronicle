// Copyright Woogle. All Rights Reserved.


#include "Character/TcCharacter.h"

#include "TcLogs.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Character/TcHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/TcPlayerController.h"
#include "Player/TcPlayerState.h"

ATcCharacter::ATcCharacter()
{
	// Avoid ticking characters if possible.
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

	HealthComponent = CreateDefaultSubobject<UTcHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;
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
	if (AbilitySystemComponent.IsValid())
	{
		return AbilitySystemComponent.Get();
	}
	return nullptr;
}

void ATcCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
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

void ATcCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATcCharacter::InitAbilitySystem()
{
	ATcPlayerState* TcPlayerState = GetPlayerState<ATcPlayerState>();
	check(TcPlayerState);
	TcPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(TcPlayerState, this);
	AbilitySystemComponent = TcPlayerState->GetTcAbilitySystemComponent();
	HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent.Get());
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

