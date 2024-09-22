// Copyright Woogle. All Rights Reserved.


#include "System/TcLibrary.h"

#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"


TArray<AActor*> UTcLibrary::GetActorsInSphere(AActor* Source, float Offset, float Radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes)
{
	FVector SphereCenter = Source->GetActorLocation() + (Source->GetActorForwardVector() * Offset);
	
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Source);
	
	TArray<AActor*> OverlappingActors;
	UKismetSystemLibrary::SphereOverlapActors(Source, SphereCenter, Radius, ObjectTypes, nullptr, IgnoredActors, OverlappingActors);

	return OverlappingActors;
}

AActor* UTcLibrary::GetClosestActorInSphere(AActor* Source, float Offset, float Radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes)
{
	TArray<AActor*> ActorsInSphere = GetActorsInSphere(Source, Offset, Radius, ObjectTypes);
	
	if (ActorsInSphere.IsEmpty())
	{
		return nullptr;
	}
	
	float MinDistance = Offset + Radius;
	AActor* ClosestActor = nullptr;
	for (AActor* Actor : ActorsInSphere)
	{
		float Distance = FVector::Dist(Source->GetActorLocation(), Actor->GetActorLocation());
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestActor = Actor;
		}
	}
	return ClosestActor;
}
