// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowEnemyCharacter.h"

#include <Components/WidgetComponent.h>

#include "CustomComponents/HealthComponent.h"
#include "HealthBarWidget.h"

ASparrowEnemyCharacter::ASparrowEnemyCharacter() : Super()
{
	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Widget"));
	HealthWidget->SetupAttachment(RootComponent);
}

void ASparrowEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthWidget)
	{
		HealthBar = Cast<UHealthBarWidget>(HealthWidget->GetWidget());
		Health->OnHealthUpdate.AddUObject(this, &ASparrowEnemyCharacter::OnHealthUpdate);
	}
}

void ASparrowEnemyCharacter::OnHealthUpdate(float MaxHealth, float CurrentHealth)
{
	if (HealthBar)
	{
		HealthBar->UpdateHealthBar(MaxHealth, CurrentHealth);
	}
}
