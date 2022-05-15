// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SparrowAnimInstance.generated.h"

class ASparrowCharacter;

USTRUCT(BlueprintType)
struct FSparrowVelocity
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		float Yaw = 0.f;

	UPROPERTY(BlueprintReadOnly)
		float Speed = 0.f;
};

USTRUCT(BlueprintType)
struct FSparrowAim
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		float Pitch = 0.f;

	UPROPERTY(BlueprintReadOnly)
		float Yaw = 0.f;
};

USTRUCT(BlueprintType)
struct FSparrowAnimState
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		bool bIsMoving = false;

	UPROPERTY(BlueprintReadOnly)
		bool bIsAiming = false;

	UPROPERTY(BlueprintReadOnly)
		bool bIsDead = false;

	UPROPERTY(BlueprintReadOnly)
		FSparrowVelocity Velocity;

	UPROPERTY(BlueprintReadOnly)
		FSparrowAim Aim;
};

UCLASS(Abstract, Blueprintable)
class BOWANDARROW_API USparrowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	void HandleVelocityUpdate();
	void HandleAimOffsetUpdate();
	float GetNewAimAngle(float Previous, float New) const;

	void OnAimStateChange(bool bIsAiming);
	void OnDeath();

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FSparrowAnimState AnimState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration", meta = (AllowPrivateAccess = "true"))
		float AimOffsetUpdateSpeed = 10.f;

	UPROPERTY()
		ASparrowCharacter* Player;
};
