// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowAnimInstance.h"

#include "SparrowCharacter.h"

void USparrowAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<ASparrowCharacter>(TryGetPawnOwner());
}

void USparrowAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Player)
	{
		return;
	}

	HandleVelocityUpdate();
}

void USparrowAnimInstance::HandleVelocityUpdate()
{
	const FVector Velocity = Player->GetVelocity();
	AnimState.Velocity.Speed = Velocity.Size();

	AnimState.bIsMoving = AnimState.Velocity.Speed > 0.f;

	const FTransform Transform{ Player->GetActorTransform() };
	AnimState.Velocity.Yaw = Transform.InverseTransformVector(Velocity).Rotation().Yaw;
}
