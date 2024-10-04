// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "TcCharacter.generated.h"

class UTcPawnExtensionComponent;
class UTcPawnData;
class ATcPlayerController;
class ATcPlayerState;
class UTcAbilitySystemComponent;
class UTcHealthComponent;

UCLASS()
class TRIBLADECHRONICLE_API ATcCharacter : public ACharacter,  public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TC|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTcPawnExtensionComponent> PawnExtComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TC|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTcHealthComponent> HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TC|Pawn Data")
	TObjectPtr<UTcPawnData> PawnData;

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

	const UTcPawnData* GetPawnData() const { return PawnData; }

protected:
	virtual void OnAbilitySystemInitialized();
	virtual void OnAbilitySystemUninitialized();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	virtual void OnRep_Controller() override;
	virtual void OnRep_PlayerState() override;

	// Begins the death sequence for the character (disables collision, disables movement, etc...)
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);

	void DisableMovementAndCollision();

private:

};
