﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeLocation(FVector(0, 0, 70));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 250;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 450;

	bUseControllerRotationYaw = false;

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), "hand_rSocket");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::CastTrace_Implementation(EEnterBranch ExecuteBranch)
{
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::MoveCharacter(float forwardInput, float rightInput)
{
	FVector forwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0));
	FVector rightVector = UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0));
	AddMovementInput(forwardVector, forwardInput);
	AddMovementInput(rightVector, rightInput);

	if((FMath::Abs(forwardInput) + FMath::Abs(rightInput)) > 0)
	{
		CalculateForcedDirection(forwardInput, rightInput);
	}
	else
	{
		inputForcedRotation = GetActorRotation();
	}
	CalculateCameraLength(interpSpeed);
}

void APlayerCharacter::Sprint(EExecuteBranch Branches)
{
	switch (Branches)
	{
	case EExecuteBranch::Pressed:
		if (LocomotionState != ELocomotionState::Walk)
		{
			GetCharacterMovement()->MaxWalkSpeed = 620;
		}
		break;
	case EExecuteBranch::Released:
		GetCharacterMovement()->MaxWalkSpeed = 450;
		break;
	default: ;
	}
}

void APlayerCharacter::Walk(EExecuteBranch Branches)
{
	switch (Branches)
	{
	case EExecuteBranch::Pressed:
		if (LocomotionState != ELocomotionState::Sprint)
		{
			GetCharacterMovement()->MaxWalkSpeed = 170;
		}
		break;
	case EExecuteBranch::Released:
		GetCharacterMovement()->MaxWalkSpeed = 450;
		break;
	default:
		GetCharacterMovement()->MaxWalkSpeed = 450;
		break;
	}
}

void APlayerCharacter::ChangeWeaponCollider_Implementation(bool bColliderActive)
{
	IWeaponCollider::ChangeWeaponCollider_Implementation(bColliderActive);
}

void APlayerCharacter::RotateCharacter(float axisTurn, float axisLook)
{
	AddControllerYawInput(axisTurn);
	AddControllerPitchInput(axisLook);
}

void APlayerCharacter::SetActionState(EActionState currentState)
{
	ActionState = currentState;

	//TODO: Fix this later.
	switch (ActionState)
	{
	case EActionState::FightMode:
		Weapon->SetHiddenInGame(false);
		break;
	case EActionState::ParkourMode:
		Weapon->SetHiddenInGame(true);
		break;
	default:
		break;
	}
}

void APlayerCharacter::SetAttack(bool value)
{
	bCanAttack = value;
}

void APlayerCharacter::CalculateCameraLength(float speedValue)
{
	float Target;
	if (ActionState == EActionState::ParkourMode)
	{
		switch (LocomotionState)
		{
		case ELocomotionState::Idle:
			Target = 200;
			break;
		case ELocomotionState::Walk:
			Target = 250;
			break;
		case ELocomotionState::Run:
			Target = 350;
			break;
		case ELocomotionState::Sprint:
			Target = 400;
			break;
		default:
			Target = 200;
			break;
		}
	}
	else
	{
		Target = 450;
	}

	SpringArm->TargetArmLength = UKismetMathLibrary::FInterpTo(SpringArm->TargetArmLength, Target,
	                                                           GetWorld()->GetDeltaSeconds(), speedValue);
}

void APlayerCharacter::CalculateForcedDirection(float forwardValue, float rightValue)
{
	FRotator forcedRotation = UKismetMathLibrary::MakeRotFromX(FVector(forwardValue, -rightValue, 0));
	FRotator deltaRotation = FRotator(0, SpringArm->GetTargetRotation().Yaw - forcedRotation.Yaw, 0);
	FVector originVector = FVector(GetCapsuleComponent()->GetForwardVector().X,
	                               GetCapsuleComponent()->GetForwardVector().Y, 0);
	inputForcedRotation = UKismetMathLibrary::FindLookAtRotation(originVector,
	                                                             UKismetMathLibrary::GetForwardVector(deltaRotation));
}

void APlayerCharacter::FocusOnTarget_Implementation()
{
}
