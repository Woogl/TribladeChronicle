// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "TcCharacter.generated.h"

class UTcHealthSet;
class UTcPawnExtensionComponent;
class UTcPawnData;
class ATcPlayerController;
class ATcPlayerState;
class UTcAbilitySystemComponent;
class UTcHealthComponent;

UCLASS()
class TRIBLADECHRONICLE_API ATcCharacter : public ACharacter,  public IAbilitySystemInterface, public IGameplayTagAssetInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
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

	UTcPawnData* GetPawnData() const { return PawnData; }

	//~Begin IGenericTeamAgentInterface
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override { MyTeamID = TeamID; }
	virtual FGenericTeamId GetGenericTeamId() const override { return MyTeamID; }
	//~End IGenericTeamAgentInterface
	
protected:
	virtual void OnAbilitySystemInitialized();
	virtual void OnAbilitySystemUninitialized();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	// Begins the death sequence for the character (disables collision, disables movement, etc...)
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);

	void DisableMovementAndCollision();

private:
	UPROPERTY(Replicated)
	FGenericTeamId MyTeamID;

private:
	UPROPERTY()
	TObjectPtr<const UTcHealthSet> HealthSet;
};
