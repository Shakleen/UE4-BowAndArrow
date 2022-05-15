// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;

UCLASS(Abstract, Blueprintable)
class BOWANDARROW_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHealthBarWidget(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable)
		void UpdateHealthBar(float MaxHealth, float CurrentHealth);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
		UProgressBar* HealthBar;
};
