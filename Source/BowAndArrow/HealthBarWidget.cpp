// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include <Components/ProgressBar.h>

UHealthBarWidget::UHealthBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHealthBarWidget::UpdateHealthBar(float MaxHealth, float CurrentHealth)
{
	if (!HealthBar || MaxHealth == 0.f || CurrentHealth < 0.f)
	{
		return;
	}

	HealthBar->SetPercent(CurrentHealth / MaxHealth);
}
