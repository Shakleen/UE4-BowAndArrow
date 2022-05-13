// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SparrowCharacter.generated.h"

class UCustomSpringArmComponent;
class UCameraComponent;

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

private:
	void BindMovementFunctions(UInputComponent* PlayerInputComponent);
	void MoveForwardOrBackward(float Value);
	void MoveRightOrLeft(float Value);
	void MoveCharacter(EAxis::Type Axis, float Value);

	void BindCameraFunctions(UInputComponent* PlayerInputComponent);

private:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UCustomSpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UCameraComponent* Camera;
};
