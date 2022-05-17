// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteor.h"

#include <Components/StaticMeshComponent.h>
#include <Particles/ParticleSystem.h>
#include <Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>

AMeteor::AMeteor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeteorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Meteor Mesh"));
	MeteorMesh->SetSimulatePhysics(true);
	SetRootComponent(MeteorMesh);

	MeteorTrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Meteor Trail Particle"));
	MeteorTrailParticle->SetupAttachment(RootComponent);
}

void AMeteor::BeginPlay()
{
	Super::BeginPlay();

	if (MeteorMesh)
	{
		MeteorMesh->OnComponentHit.AddDynamic(this, &AMeteor::OnMeteorHit);
	}
}

void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeteor::OnMeteorHit(
	UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, 
	const FHitResult& Hit
) {
	if (!ExplosionParticles)
	{
		return;
	}

	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		ExplosionParticles,
		Hit.ImpactPoint,
		FRotator::ZeroRotator,
		ExplosionScale
	);
	OnImpact.Broadcast();
	Destroy();
}

