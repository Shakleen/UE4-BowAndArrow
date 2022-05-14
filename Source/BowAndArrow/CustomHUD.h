// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"

class ASparrowCharacter;

UCLASS()
class BOWANDARROW_API ACustomHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void OnAimStateChange(bool bIsAiming);

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> CrossHairWidgetClass;

	UPROPERTY()
		UUserWidget* CrossHairWidget;

	UPROPERTY()
		ASparrowCharacter* Player;
};
