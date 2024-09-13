// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "TcCharacter.generated.h"

class ATcPlayerController;
class ATcPlayerState;
class UAttributeSet;
class UTcAbilitySet;
class UTcAbilitySystemComponent;
class UAbilitySystemComponent;
class UTcHealthComponent;

UCLASS(Abstract)
class TRIBLADECHRONICLE_API ATcCharacter : public ACharacter,  public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UTcAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TC|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTcHealthComponent> HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn Data")
	TObjectPtr<UTcAbilitySet> AbilitySet;

public:
	ATcCharacter();

	UFUNCTION(BlueprintCallable, Category = "TC|Character")
	ATcPlayerController* GetTcPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "TC|Character")
	ATcPlayerState* GetTcPlayerState() const;
	
	// IAbilitySystemInterface
	UFUNCTION(BlueprintCallable, Category = "TC|Character")
	UTcAbilitySystemComponent* GetTcAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	
	void ToggleCrouch();

protected:
	virtual void BeginPlay() override;
	void InitAbilitySystem();

	// Begins the death sequence for the character (disables collision, disables movement, etc...)
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);

	void DisableMovementAndCollision();
};
