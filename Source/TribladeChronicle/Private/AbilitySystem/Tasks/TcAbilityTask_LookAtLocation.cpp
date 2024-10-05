// Copyright Woogle. All Rights Reserved.


#include "AbilitySystem/Tasks/TcAbilityTask_LookAtLocation.h"

#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

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

void UTcAbilityTask_LookAtLocation::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(ThisClass, Duration);
	DOREPLIFETIME(ThisClass, TargetLocation);
}

void UTcAbilityTask_LookAtLocation::InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent)
{
	Super::InitSimulatedTask(InGameplayTasksComponent);

	StartTime = GetWorld()->GetTimeSeconds();
	EndTime = StartTime + Duration;
}

UTcAbilityTask_LookAtLocation* UTcAbilityTask_LookAtLocation::LookAtLocation(UGameplayAbility* OwningAbility, FVector TargetLocation, float Duration, bool bEaseIn, bool bEaseOut)
{
	UTcAbilityTask_LookAtLocation* MyTask = NewAbilityTask<UTcAbilityTask_LookAtLocation>(OwningAbility);
	MyTask->TargetLocation = TargetLocation;
	MyTask->Duration = FMath::Max(Duration, 0.001f);
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
	TargetRotation.Pitch = GetAvatarActor()->GetActorRotation().Pitch;
	TargetRotation.Roll = GetAvatarActor()->GetActorRotation().Roll;
	
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
