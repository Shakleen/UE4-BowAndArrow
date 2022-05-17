// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SparrowCharacter.generated.h"

class UCustomSpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class AArrow;
class UHealthComponent;
class USparrowUltimateComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAimStateChangeDelegate, bool bIsAiming);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUltimateAimDelegate, bool bIsAiming);

USTRUCT(BlueprintType)
struct FSparrowState
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsAimingBow = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsAimingUltimate = false;
};

UCLASS(Abstract, Blueprintable)
class BOWANDARROW_API ASparrowCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASparrowCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
public:
	FOnAimStateChangeDelegate OnAimStateChange;
	FOnUltimateAimDelegate OnUltimateAim;

private:
	void BindMovementFunctions(UInputComponent* PlayerInputComponent);
	void MoveForwardOrBackward(float Value);
	void MoveRightOrLeft(float Value);
	void MoveCharacter(EAxis::Type Axis, float Value);

	void BindCameraFunctions(UInputComponent* PlayerInputComponent);

	void BindAimingFunctions(UInputComponent* PlayerInputComponent);
	void AimBow();
	void LowerBow();
	void SetAimMode(bool bIsAiming);

	void BindFiringFunctions(UInputComponent* PlayerInputComponent);
	void FireArrow();

	void BindUltimateFunctions(UInputComponent* PlayerInputComponent);
	void AimUltimate();
	void ReleaseUltimate();
	void SetUltimateRange(float AxisValue);

	void SpawnArrow();

	void SetControlRotationStatus(bool bIsAiming);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
		UCustomSpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UHealthComponent* Health;

	UPROPERTY(VisibleAnywhere, Category = Components)
		USparrowUltimateComponent* Ultimate;

	UPROPERTY(EditAnywhere, Category = Configurations)
		float MaxAimingSpeed = 150.f;

	UPROPERTY(EditAnywhere, Category = Configurations)
		float MaxNonAimingSpeed = 600.f;
	
	UPROPERTY(EditAnywhere, Category = Configurations)
		float UltimateRange = 5000.f;

	UPROPERTY(EditAnywhere, Category = Configurations)
		UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, Category = Configurations)
		TSubclassOf<AArrow> ArrowClass;

	UPROPERTY(VisibleAnywhere, Category = State)
		FSparrowState State;

	UPROPERTY()
		UCharacterMovementComponent* SparrowMovement;
};
