// Copyright Woogle. All Rights Reserved.


#include "AbilitySystem/Tasks/TcAbilityTask_LookAtLocation.h"

#include "Kismet/KismetMathLibrary.h"

UTcAbilityTask_LookAtLocation::UTcAbilityTask_LookAtLocation()
{
	bTickingTask = true;
	bSimulatedTask = true;

	Duration = 0.f;
	StartTime = 0.f;
	EndTime = 0.f;

	bEaseIn = false;
	bEaseOut = false;
	
	TargetLocation = FVector::ZeroVector;
}

UTcAbilityTask_LookAtLocation* UTcAbilityTask_LookAtLocation::LookAtLocation(UGameplayAbility* OwningAbility, FVector TargetLocation, float Duration, bool bEaseIn, bool bEaseOut)
{
	UTcAbilityTask_LookAtLocation* MyTask = NewAbilityTask<UTcAbilityTask_LookAtLocation>(OwningAbility);
	MyTask->TargetLocation = TargetLocation;
	MyTask->Duration = Duration;
	MyTask->bEaseIn = bEaseIn;
	MyTask->bEaseOut = bEaseOut;
	return MyTask;
}

void UTcAbilityTask_LookAtLocation::Activate()
{
	Super::Activate();

	StartTime = GetWorld()->GetTimeSeconds();
	EndTime = StartTime + Duration;
}

void UTcAbilityTask_LookAtLocation::TickTask(float DeltaTime)
{
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetAvatarActor()->GetActorLocation(), TargetLocation);
	float Alpha = (GetWorld()->GetTimeSeconds() - StartTime) / Duration;
	
	FRotator NewRotation;
	if (!bEaseIn && !bEaseOut)
	{
		NewRotation = FMath::Lerp(GetAvatarActor()->GetActorRotation(), TargetRotation, Alpha);
	}
	else if (bEaseIn && !bEaseOut)
	{
		NewRotation = FMath::InterpEaseIn(GetAvatarActor()->GetActorRotation(), TargetRotation, Alpha, 2);
	}
	else if (!bEaseIn && bEaseOut)
	{
		NewRotation = FMath::InterpEaseOut(GetAvatarActor()->GetActorRotation(), TargetRotation, Alpha, 2);
	}
	else if (bEaseIn && bEaseOut)
	{
		NewRotation = FMath::InterpEaseInOut(GetAvatarActor()->GetActorRotation(), TargetRotation, Alpha, 2);
	}

	GetAvatarActor()->SetActorRotation(NewRotation);

	if (GetWorld()->GetTimeSeconds() >= EndTime || FMath::IsNearlyEqual(GetAvatarActor()->GetActorRotation().Yaw, TargetRotation.Yaw))
	{
		EndTask();
	}
}
