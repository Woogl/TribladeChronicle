// Copyright Woogle. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TcLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TRIBLADECHRONICLE_API UTcLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TC|Targeting")
	static TArray<AActor*> GetActorsInSphere(AActor* Source, float Offset, float Radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes);

	UFUNCTION(BlueprintCallable, Category = "TC|Targeting")
	static AActor* GetClosestActorInSphere(AActor* Source, float Offset, float Radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes);
};
