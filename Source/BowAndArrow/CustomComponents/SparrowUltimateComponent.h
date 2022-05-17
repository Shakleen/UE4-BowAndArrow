// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "SparrowUltimateComponent.generated.h"

class UDecalComponent;
class ASparrowCharacter;
class AMeteor;

UCLASS()
class BOWANDARROW_API USparrowUltimateComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void AimUltimate(float DeltaTime);
	void SetDirection(float AxisValue);
	void DropMeteor();

protected:
	virtual void BeginPlay() override;

private:
	void SetupProjectileParams();
	void SetStartLocationAndLaunchVelocity();
	FVector CalculateLaunchVelocity(const FTransform& SocketTransform);
	void UpdateWorldLocation();
	FVector GetMeteorSpawnLocation() const;

private:
	UPROPERTY(EditAnywhere, Category = Configuration)
		bool bDebug = false;

	UPROPERTY(EditAnywhere, Category = Configuration)
		float Speed = 1000.f;

	UPROPERTY(EditAnywhere, Category = Configuration)
		float RangeChangeSmoothness = 10.f;

	UPROPERTY(EditAnywhere, Category = Configuration)
		float RangeChangeInterpSpeed = 25.f;

	UPROPERTY(EditAnywhere, Category = Configuration)
		float MaxRange = 0.3f;

	UPROPERTY(EditAnywhere, Category = Configuration)
		float MinRange = 0.f;

	UPROPERTY(EditAnywhere, Category = Configuration)
		float MeteorSpawnHeight = 1000.f;

	UPROPERTY(EditAnywhere, Category = Configuration)
		TSubclassOf<AMeteor> MeteorClass;

	UPROPERTY(VisibleAnywhere, Transient, Category = Configuration)
		float Direction = 0.f;

	UPROPERTY(EditAnywhere, Category = Configuration)
		float LocationChangeInterpSpeed = 5.f;

	ASparrowCharacter* Sparrow;
	FPredictProjectilePathParams Params;
	FPredictProjectilePathResult Result;
};
