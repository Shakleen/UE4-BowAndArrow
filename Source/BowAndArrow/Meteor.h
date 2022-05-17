// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Meteor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

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
	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* MeteorMesh;

	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* MeteorCollision;
};
