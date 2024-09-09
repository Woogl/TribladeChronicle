// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "TcCharacter.generated.h"

class UAttributeSet;
class UTcAbilitySet;
class UTcAbilitySystemComponent;
class UAbilitySystemComponent;

UCLASS(Abstract)
class TRIBLADECHRONICLE_API ATcCharacter : public ACharacter,  public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UTcAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn Data")
	TObjectPtr<UTcAbilitySet> AbilitySet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn Data")
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	ATcCharacter();
	
	// IAbilitySystemInterface
	UFUNCTION(BlueprintCallable, Category = "Tc|Character")
	UTcAbilitySystemComponent* GetTcAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	void InitAbilitySystem();
};
