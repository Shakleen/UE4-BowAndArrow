// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

class UStaticMeshComponent;

UCLASS(Abstract, Blueprintable)
class BOWANDARROW_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	AArrow();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Launch(const FTransform& MuzzleTransform);

private:
	UFUNCTION()
		void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = Configuration)
		float LaunchStrength = 1000;

	UPROPERTY(EditAnywhere, Category = Configuration)
		uint32 DamageAmount = 25;
};
