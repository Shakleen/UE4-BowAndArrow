// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"

#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>

AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Mesh"));
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetGenerateOverlapEvents(true);
	SetRootComponent(StaticMesh);
}

void AArrow::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentHit.AddDynamic(this, &AArrow::OnComponentHit);
}

void AArrow::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *OtherActor->GetName());

	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Destroy();
}

void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AArrow::Launch(const FTransform& MuzzleTransform)
{
	FRotator MuzzleRotation = MuzzleTransform.Rotator();
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(MuzzleRotation);
	StaticMesh->AddImpulse(ForwardVector * LaunchStrength);
}

