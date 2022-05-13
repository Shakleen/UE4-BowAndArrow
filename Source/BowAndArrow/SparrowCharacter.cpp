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
}

