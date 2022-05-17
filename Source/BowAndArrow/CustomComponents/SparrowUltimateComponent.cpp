// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowUltimateComponent.h"

#include <Kismet/GameplayStatics.h>

#include "../SparrowCharacter.h"
#include "../Meteor.h"

void USparrowUltimateComponent::BeginPlay()
{
	Super::BeginPlay();

	SetVisibility(false);
	SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetGenerateOverlapEvents(true);
	Sparrow = Cast<ASparrowCharacter>(GetOwner());
	SetupProjectileParams();
	Direction = MinRange;
}

void USparrowUltimateComponent::SetupProjectileParams()
{
	Params.DrawDebugType = bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
	Params.bTraceWithCollision = true;
	Params.SimFrequency = 4.f;
	Params.MaxSimTime = 10.f;
	Params.DrawDebugTime = 0.f;
	Params.OverrideGravityZ = 0.f;
	Params.ObjectTypes = TArray<TEnumAsByte<EObjectTypeQuery>>();
	Params.ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	Params.ActorsToIgnore = TArray<AActor*>({ Sparrow });
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
	FTransform SocketTransform = Sparrow->GetMesh()->GetSocketTransform(TEXT("BowEmitterSocket"));
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

void USparrowUltimateComponent::DropMeteor()
{
	if (!MeteorClass)
	{
		return;
	}

	AMeteor* Meteor = GetWorld()->SpawnActor<AMeteor>(MeteorClass);

	if (Meteor)
	{
		Meteor->SetActorLocation(GetMeteorSpawnLocation());
		Meteor->OnImpact.AddUObject(this, &USparrowUltimateComponent::OnMeteorImpact);
	}
}

FVector USparrowUltimateComponent::GetMeteorSpawnLocation() const
{
	FVector HitLocation = Result.LastTraceDestination.Location;
	FVector SpawnLocation = HitLocation + FVector(0.f, 0.f, MeteorSpawnHeight);
	return SpawnLocation;
}

void USparrowUltimateComponent::OnMeteorImpact()
{
	FTimerHandle HideTimer;

	Sparrow->GetWorldTimerManager().SetTimer(
		HideTimer,
		this,
		&USparrowUltimateComponent::Hide,
		AimHideDelay
	);

	TSet<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, TSubclassOf<ASparrowCharacter>());

	for (auto &OverlappingActor : OverlappingActors)
	{
		OverlappingActor->TakeDamage(
			DamageAmount,
			FDamageEvent(),
			UGameplayStatics::GetPlayerController(GetWorld(), 0),
			Sparrow
		);
	}
}

void USparrowUltimateComponent::Hide()
{
	SetVisibility(false, true);
	Direction = MinRange;
}
