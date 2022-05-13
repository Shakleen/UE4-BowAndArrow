// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowCharacter.h"

ASparrowCharacter::ASparrowCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASparrowCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASparrowCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASparrowCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindMovementFunctions(PlayerInputComponent);
}

#pragma region Movement function bindings

void ASparrowCharacter::BindMovementFunctions(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(
		TEXT("Move Forward / Backward"),
		this,
		&ASparrowCharacter::MoveForwardOrBackward
	);
	PlayerInputComponent->BindAxis(
		TEXT("Move Right / Left"),
		this,
		&ASparrowCharacter::MoveRightOrLeft
	);
}


void ASparrowCharacter::MoveForwardOrBackward(float Value)
{
	MoveCharacter(EAxis::X, Value);
}

void ASparrowCharacter::MoveRightOrLeft(float Value)
{
	MoveCharacter(EAxis::Y, Value);
}

void ASparrowCharacter::MoveCharacter(EAxis::Type Axis, float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector UnitDirection = FRotationMatrix(YawRotation).GetUnitAxis(Axis);
	AddMovementInput(UnitDirection, Value);
}

#pragma endregion Movement function bindings
