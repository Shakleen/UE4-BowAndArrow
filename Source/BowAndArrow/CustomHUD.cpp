// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUD.h"

#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>

#include "SparrowCharacter.h"

void ACustomHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!CrossHairWidgetClass)
	{
		return;
	}

	CrossHairWidget = CreateWidget<UUserWidget>(GetWorld(), CrossHairWidgetClass);
	Player = Cast<ASparrowCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (Player)
	{
		Player->OnAimStateChange.AddUObject(this, &ACustomHUD::OnAimStateChange);
	}
}

void ACustomHUD::OnAimStateChange(bool bIsAiming)
{
	if (!CrossHairWidget)
	{
		return;
	}

	if (bIsAiming)
	{
		CrossHairWidget->AddToViewport();
	}
	else
	{
		CrossHairWidget->RemoveFromViewport();
	}
}
