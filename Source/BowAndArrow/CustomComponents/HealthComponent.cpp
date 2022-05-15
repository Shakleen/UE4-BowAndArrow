// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = MaxHealth;
}

void UHealthComponent::PostInitProperties()
{
	Super::PostInitProperties();

	CurrentHealth = MaxHealth;
}

#ifdef WITH_EDITOR

void UHealthComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	CurrentHealth = MaxHealth;
}

#endif

bool UHealthComponent::IsEmpty() const
{
	return CurrentHealth == 0;
}

bool UHealthComponent::IsFull() const
{
	return CurrentHealth == MaxHealth;
}

uint32 UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

uint32 UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UHealthComponent::TakeDamage(uint32 Amount)
{
	SetCurrentHealth(CurrentHealth - Amount);
}

void UHealthComponent::SetCurrentHealth(uint32 NewValue)
{
	CurrentHealth = FMath::Clamp(uint32(0), MaxHealth, NewValue);
}

