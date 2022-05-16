// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowUltimateComponent.h"

#include <Kismet/GameplayStatics.h>

#include "../SparrowCharacter.h"

void USparrowUltimateComponent::BeginPlay()
{
	Super::BeginPlay();

	SetVisibility(false);
	SetCollisionProfileName(TEXT("NoCollision"));

	Sparrow = Cast<ASparrowCharacter>(GetOwner());

	Params.bTraceWithCollision = true;
	Params.SimFrequency = 12.f;
	Params.MaxSimTime = 10.f;
	Params.DrawDebugTime = 0.f;
	Params.OverrideGravityZ = 0.f;
	Params.ObjectTypes = TArray<TEnumAsByte<EObjectTypeQuery>>();
	Params.ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	Params.ActorsToIgnore = TArray<AActor*>({ Sparrow });
	Params.DrawDebugType = EDrawDebugTrace::ForDuration;
}

void USparrowUltimateComponent::AimUltimate(float DeltaTime)
{
	if (!Sparrow)
	{
		return;
	}

	SetStartLocationAndLaunchVelocity();
	UGameplayStatics::PredictProjectilePath(GetOwner(), Params, Result);
	UpdateWorldLocation();
}

void USparrowUltimateComponent::SetStartLocationAndLaunchVelocity()
{
	FTransform SocketTransform = Sparrow->GetMesh()->GetSocketTransform(TEXT("Ultimate Socket"));
	Params.StartLocation = SocketTransform.GetLocation();
	Params.LaunchVelocity = CalculateLaunchVelocity(SocketTransform);
}

FVector USparrowUltimateComponent::CalculateLaunchVelocity(const FTransform& SocketTransform)
{
	FVector LaunchVelocity = SocketTransform.GetRotation().GetForwardVector();
	LaunchVelocity *= (1.f + Direction);
	LaunchVelocity *= Speed;
	return LaunchVelocity;
}

inline void USparrowUltimateComponent::UpdateWorldLocation()
{
	FVector CurrentLocation = GetComponentLocation();
	FVector NewLocation = FMath::VInterpTo(
		CurrentLocation,
		Result.LastTraceDestination.Location,
		GetWorld()->GetDeltaSeconds(),
		LocationChangeInterpSpeed
	);
	SetWorldLocation(NewLocation);
}

void USparrowUltimateComponent::SetDirection(float AxisValue)
{
	const float TargetDirection = Direction + AxisValue / RangeChangeSmoothness;
	const float NewDirection = FMath::FInterpTo(
		Direction,
		TargetDirection,
		GetWorld()->GetDeltaSeconds(),
		RangeChangeInterpSpeed
	);

	if (NewDirection >= MinRange && NewDirection <= MaxRange)
	{
		Direction = NewDirection;
	}
}
