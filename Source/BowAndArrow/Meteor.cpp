// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteor.h"

#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

AMeteor::AMeteor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeteorCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Meteor Collision"));
	SetRootComponent(MeteorCollision);

	MeteorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Meteor Mesh"));
	MeteorMesh->SetCollisionProfileName(TEXT("NoCollision"));
	MeteorMesh->SetupAttachment(RootComponent);
}

void AMeteor::BeginPlay()
{
	Super::BeginPlay();
}

void AMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

