// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SparrowCharacter.generated.h"

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

};
