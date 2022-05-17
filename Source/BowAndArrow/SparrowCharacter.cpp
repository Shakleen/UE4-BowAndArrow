// Fill out your copyright notice in the Description page of Project Settings.


#include "SparrowCharacter.h"

#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>
#include <DrawDebugHelpers.h>

#include "CustomComponents/CustomSpringArmComponent.h"
#include "CustomComponents/HealthComponent.h"
#include "CustomComponents/SparrowUltimateComponent.h"
#include "Arrow.h"

ASparrowCharacter::ASparrowCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<UCustomSpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	AddOwnedComponent(Health);

	Ultimate = CreateDefaultSubobject<USparrowUltimateComponent>(TEXT("Ultimate"));
	Ultimate->SetupAttachment(RootComponent);
}

void ASparrowCharacter::BeginPlay()
{
	Super::BeginPlay();

	SparrowMovement = GetCharacterMovement();
	LowerBow();
}

void ASparrowCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (State.bIsAimingUltimate)
	{
		Ultimate->AimUltimate(DeltaTime);
	}
}

void ASparrowCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindMovementFunctions(PlayerInputComponent);
	BindCameraFunctions(PlayerInputComponent);
	BindAimingFunctions(PlayerInputComponent);
	BindFiringFunctions(PlayerInputComponent);
	BindUltimateFunctions(PlayerInputComponent);
}

float ASparrowCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	float AppliedDamage = Health->TakeDamage(Damage);
	return AppliedDamage;
}

void ASparrowCharacter::ToggleAnimation(bool bPlay)
{
	GetMesh()->bPauseAnims = !bPlay;
}

#pragma region Movement function bindings

inline void ASparrowCharacter::BindMovementFunctions(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(
		TEXT("Move Forward / Backward"),
		this,
		&ASparrowCharacter::MoveForwardOrBackward
	);
	PlayerInputComponent->BindAxis(
		TEXT("Move Right / Left"),
		this,
		&ASparrowCharacter::MoveRightOrLeft
	);
}


void ASparrowCharacter::MoveForwardOrBackward(float Value)
{
	if (State.bIsAimingUltimate)
	{
		return;
	}

	MoveCharacter(EAxis::X, Value);
}

void ASparrowCharacter::MoveRightOrLeft(float Value)
{
	if (State.bIsAimingUltimate)
	{
		return;
	}

	MoveCharacter(EAxis::Y, Value);
}

void ASparrowCharacter::MoveCharacter(EAxis::Type Axis, float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector UnitDirection = FRotationMatrix(YawRotation).GetUnitAxis(Axis);
	AddMovementInput(UnitDirection, Value);
}

#pragma endregion Movement function bindings

#pragma region Camera function bindings

inline void ASparrowCharacter::BindCameraFunctions(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(
		TEXT("Look Up / Down Mouse"),
		this,
		&ACharacter::AddControllerPitchInput
	);
	PlayerInputComponent->BindAxis(
		TEXT("Turn Right / Left Mouse"),
		this,
		&ACharacter::AddControllerYawInput
	);
}

#pragma endregion Camera function bindings

#pragma region Aiming function bindings

inline void ASparrowCharacter::BindAimingFunctions(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(
		TEXT("Aim"),
		EInputEvent::IE_Pressed,
		this,
		&ASparrowCharacter::AimBow
	);
	PlayerInputComponent->BindAction(
		TEXT("Aim"),
		EInputEvent::IE_Released,
		this,
		&ASparrowCharacter::LowerBow
	);
}

void ASparrowCharacter::AimBow()
{
	SetAimMode(true);
}

void ASparrowCharacter::LowerBow()
{
	SetAimMode(false);
}

inline void ASparrowCharacter::SetAimMode(bool bIsAiming)
{
	if (!SparrowMovement || State.bIsAimingUltimate)
	{
		return;
	}

	State.bIsAimingBow = bIsAiming;
	SparrowMovement->MaxWalkSpeed = bIsAiming ? MaxAimingSpeed : MaxNonAimingSpeed;
	SetControlRotationStatus(bIsAiming);
	OnAimStateChange.Broadcast(bIsAiming);
}

#pragma endregion Aiming function bindings

#pragma region Firing function bindings

inline void ASparrowCharacter::BindFiringFunctions(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(
		TEXT("Fire"),
		EInputEvent::IE_Pressed,
		this,
		&ASparrowCharacter::FireArrow
	);
}

void ASparrowCharacter::FireArrow()
{
	if (!State.bIsAimingBow || !FireMontage)
	{
		return;
	}

	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(FireMontage))
	{
		return;
	}
	
	PlayAnimMontage(FireMontage);
	SpawnArrow();
}

void ASparrowCharacter::SpawnArrow()
{
	if (!ArrowClass)
	{
		return;
	}

	AArrow* Arrow = GetWorld()->SpawnActor<AArrow>(ArrowClass);

	if (Arrow)
	{
		FTransform MuzzleTransform = GetMesh()->GetSocketTransform(TEXT("BowEmitterSocket"));
		Arrow->SetActorTransform(MuzzleTransform);
		Arrow->Launch(MuzzleTransform);
	}
}

#pragma endregion Firing function bindings

void ASparrowCharacter::BindUltimateFunctions(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(
		TEXT("Ultimate"),
		EInputEvent::IE_Pressed,
		this,
		&ASparrowCharacter::AimUltimate
	);
	PlayerInputComponent->BindAction(
		TEXT("Ultimate"),
		EInputEvent::IE_Released,
		this,
		&ASparrowCharacter::ReleaseUltimate
	);

	PlayerInputComponent->BindAxis(
		TEXT("Control Ultimate Range"),
		this,
		&ASparrowCharacter::SetUltimateRange
	);
}

void ASparrowCharacter::AimUltimate()
{
	if (State.bIsAimingBow)
	{
		return;
	}

	State.bIsAimingUltimate = true;
	Ultimate->SetVisibility(true, true);
	SetControlRotationStatus(true);

	if (UltAbilityMontage)
	{
		PlayAnimMontage(UltAbilityMontage);
	}
}

void ASparrowCharacter::ReleaseUltimate()
{
	State.bIsAimingUltimate = false;
	Ultimate->SetVisibility(false, true);
	Ultimate->DropMeteor();
	SetControlRotationStatus(false);
	ToggleAnimation(true);
}

void ASparrowCharacter::SetUltimateRange(float AxisValue)
{
	if (State.bIsAimingUltimate && Ultimate)
	{
		Ultimate->SetDirection(AxisValue);
	}
}

void ASparrowCharacter::SetControlRotationStatus(bool bIsAiming)
{
	SparrowMovement->bOrientRotationToMovement = !bIsAiming;
	bUseControllerRotationYaw = bIsAiming;
}
