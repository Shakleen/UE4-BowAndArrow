// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Meteor.generated.h"

class UStaticMeshComponent;
class UParticleSystem;
class UParticleSystemComponent;

DECLARE_MULTICAST_DELEGATE(FOnImpactDelegate);

UCLASS(Abstract, Blueprintable)
class BOWANDARROW_API AMeteor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMeteor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnMeteorHit(
			UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit
		);

public:
	FOnImpactDelegate OnImpact;

private:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* MeteorMesh;

	UPROPERTY(EditAnywhere, Category = Components)
		UParticleSystemComponent* MeteorTrailParticle;

	UPROPERTY(EditAnywhere, Category = Configurations)
		UParticleSystem* ExplosionParticles;

	UPROPERTY(EditAnywhere, Category = Configurations)
		FVector ExplosionScale = FVector(1.f);
};
