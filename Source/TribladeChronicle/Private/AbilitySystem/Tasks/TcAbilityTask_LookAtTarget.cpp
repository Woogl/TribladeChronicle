// Copyright Woogle. All Rights Reserved.


#include "AbilitySystem/Tasks/TcAbilityTask_LookAtTarget.h"

#include "Kismet/KismetMathLibrary.h"

UTcAbilityTask_LookAtTarget::UTcAbilityTask_LookAtTarget()
{
	bTickingTask = true;
	bSimulatedTask = true;

	Duration = 0.f;
	StartTime = 0.f;
	EndTime = 0.f;

	bEaseIn = false;
	bEaseOut = false;
	
	TargetActor = nullptr;
}

UTcAbilityTask_LookAtTarget* UTcAbilityTask_LookAtTarget::LookAtTarget(UGameplayAbility* OwningAbility, AActor* TargetActor, float Duration, bool bEaseIn, bool bEaseOut)
{
	UTcAbilityTask_LookAtTarget* MyTask = NewAbilityTask<UTcAbilityTask_LookAtTarget>(OwningAbility);
	if (TargetActor)
	{
		MyTask->TargetActor = TargetActor;
	}
	MyTask->Duration = Duration;
	MyTask->bEaseIn = bEaseIn;
	MyTask->bEaseOut = bEaseOut;
	return MyTask;
}

void UTcAbilityTask_LookAtTarget::Activate()
{
	Super::Activate();

	StartTime = GetWorld()->GetTimeSeconds();
	EndTime = StartTime + Duration;
}

void UTcAbilityTask_LookAtTarget::TickTask(float DeltaTime)
{
	if (TargetActor == nullptr)
	{
		EndTask();
		return;
	}
	
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetAvatarActor()->GetActorLocation(), TargetActor->GetActorLocation());
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
