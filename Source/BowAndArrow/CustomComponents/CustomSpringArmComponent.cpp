// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSpringArmComponent.h"

#include <TimerManager.h>
#include <GameFramework/Actor.h>

#include "../SparrowCharacter.h"

#define IS_EQUAL(Value1, Value2) FMath::Abs(Value1 - Value2) < 1e-4

void UCustomSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	ASparrowCharacter* OwningPlayer = Cast<ASparrowCharacter>(GetOwner());
	if (!OwningPlayer) return;
	OwningPlayer->OnAimStateChange.AddUObject(this, &UCustomSpringArmComponent::OnAimStanceChange);
}

void UCustomSpringArmComponent::OnAimStanceChange(bool bAiming)
{
	bIsAiming = bAiming;
	StartPerspectiveTransition();
}

void UCustomSpringArmComponent::StartPerspectiveTransition()
{
	if (GetOwner()->GetWorldTimerManager().IsTimerActive(PerspectiveTransitionTimer))
	{
		return;
	}

	GetOwner()->GetWorldTimerManager().SetTimer(
		PerspectiveTransitionTimer,
		this,
		&UCustomSpringArmComponent::Transition,
		0.01f,
		true
	);
}

void UCustomSpringArmComponent::Transition()
{
	FSpringArmConfig OutcomeAimMode = bIsAiming ? AimPerspective : ThirdPersonPerspective;

	if (IS_EQUAL(TargetArmLength, OutcomeAimMode.TargetArmLength))
	{
		StopPerspectiveTransition();
		return;
	}

	float Alpha = AimTransitionSpeed * GetWorld()->GetDeltaSeconds();

	SocketOffset = FMath::Lerp(SocketOffset, OutcomeAimMode.SocketOffset, Alpha);
	TargetArmLength = FMath::Lerp(TargetArmLength, OutcomeAimMode.TargetArmLength, Alpha);
}

void UCustomSpringArmComponent::StopPerspectiveTransition()
{
	if (GetOwner()->GetWorldTimerManager().IsTimerActive(PerspectiveTransitionTimer))
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(PerspectiveTransitionTimer);
	}
}