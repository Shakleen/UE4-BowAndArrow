// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOWANDARROW_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	bool IsEmpty() const;
	bool IsFull() const;
	uint32 GetCurrentHealth() const;
	uint32 GetMaxHealth() const;
	uint32 TakeDamage(uint32 Amount);
	void SetCurrentHealth(uint32 NewValue);

private:
	virtual void PostInitProperties() override;

#ifdef WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	UPROPERTY(EditAnywhere, Category = Configuration)
		uint32 MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Transient, Category = Configuration)
		uint32 CurrentHealth = 0;
};
