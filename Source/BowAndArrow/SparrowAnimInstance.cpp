// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowAnimInstance.h"

#include "SparrowCharacter.h"

void USparrowAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<ASparrowCharacter>(TryGetPawnOwner());

	if (Player)
	{
		Player->OnAimStateChange.AddUObject(this, &USparrowAnimInstance::OnAimStateChange);
	}
}

void USparrowAnimInstance::OnAimStateChange(bool bIsAiming)
{
	AnimState.bIsAiming = bIsAiming;
}


void USparrowAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Player)
	{
		return;
	}

	HandleVelocityUpdate();
	HandleAimOffsetUpdate();
}

void USparrowAnimInstance::HandleVelocityUpdate()
{
	const FVector Velocity = Player->GetVelocity();
	AnimState.Velocity.Speed = Velocity.Size();

	AnimState.bIsMoving = AnimState.Velocity.Speed > 0.f;

	const FTransform Transform{ Player->GetActorTransform() };
	AnimState.Velocity.Yaw = Transform.InverseTransformVector(Velocity).Rotation().Yaw;
}

void USparrowAnimInstance::HandleAimOffsetUpdate()
{
	FRotator NewAimRotation = (Player->GetBaseAimRotation() - Player->GetActorRotation());
	AnimState.Aim.Pitch = GetNewAimAngle(NewAimRotation.Pitch, AnimState.Aim.Pitch);
	AnimState.Aim.Yaw = GetNewAimAngle(NewAimRotation.Yaw, AnimState.Aim.Yaw);
}

float USparrowAnimInstance::GetNewAimAngle(float Previous, float New) const
{
	float Current = FMath::FInterpTo(Previous, New, GetWorld()->GetDeltaSeconds(), AimOffsetUpdateSpeed);
	return FMath::ClampAngle(Current, -90.f, 90.f);
}