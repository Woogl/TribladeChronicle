// Copyright Woogle. All Rights Reserved.


#include "AbilitySystem/Attributes/TcAttributeSet.h"

#include "AbilitySystem/TcAbilitySystemComponent.h"

UWorld* UTcAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UTcAbilitySystemComponent* UTcAttributeSet::GetTcAbilitySystemComponent() const
{
	return Cast<UTcAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
