// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SparrowCharacter.h"
#include "SparrowEnemyCharacter.generated.h"

class UWidgetComponent;
class UHealthBarWidget;

UCLASS()
class BOWANDARROW_API ASparrowEnemyCharacter : public ASparrowCharacter
{
	GENERATED_BODY()

public:
	ASparrowEnemyCharacter();

protected:
	virtual void BeginPlay() override;

private:
	void OnHealthUpdate(float MaxHealth, float CurrentHealth);

private:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UWidgetComponent* HealthWidget;

	UPROPERTY()
		UHealthBarWidget* HealthBar;
};
