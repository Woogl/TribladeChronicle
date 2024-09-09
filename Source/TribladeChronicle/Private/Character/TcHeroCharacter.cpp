// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TcHeroCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/TcAbilitySet.h"
#include "AbilitySystem/TcAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/TcInputComponent.h"

ATcHeroCharacter::ATcHeroCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ATcHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilitySystem();
	
	if (AbilitySet)
	{
		AbilitySet->GiveToAbilitySystem(GetAbilitySystemComponent(), this);
	}
}

void ATcHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilitySystem();
}

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
		TcInputComp->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
		
		TcInputComp->BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag(FName("Input.Move")), ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
		TcInputComp->BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag(FName("Input.Look")), ETriggerEvent::Triggered, this, &ThisClass::Input_Look, false);
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
