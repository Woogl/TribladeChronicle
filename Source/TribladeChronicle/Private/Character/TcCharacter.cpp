// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TcCharacter.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/TcPlayerState.h"

ATcCharacter::ATcCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
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
	AttributeSet = TcPlayerState->GetAttributeSet();
}

