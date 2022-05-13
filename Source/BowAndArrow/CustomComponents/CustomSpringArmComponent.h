// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "CustomSpringArmComponent.generated.h"

USTRUCT(BlueprintType)
struct FSpringArmConfig
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		float TargetArmLength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		FVector SocketOffset;

	FSpringArmConfig() : TargetArmLength(300.f), SocketOffset(FVector(0.f)) {	}
};

UCLASS()
class BOWANDARROW_API UCustomSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void OnAimStanceChange(bool bAiming);
	void StartPerspectiveTransition();
	void Transition();
	void StopPerspectiveTransition();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration", meta = (AllowPrivateAccess = "true"))
		FSpringArmConfig ThirdPersonPerspective;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration", meta = (AllowPrivateAccess = "true"))
		FSpringArmConfig AimPerspective;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration", meta = (AllowPrivateAccess = "true", ClampMin = "0.1"))
		float AimTransitionUpdateFrequency = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration", meta = (AllowPrivateAccess = "true", ClampMin = "1"))
		float AimTransitionSpeed = 10.f;

	UPROPERTY()
		FTimerHandle PerspectiveTransitionTimer;
	UPROPERTY()
		bool bIsAiming = false;
	
};
