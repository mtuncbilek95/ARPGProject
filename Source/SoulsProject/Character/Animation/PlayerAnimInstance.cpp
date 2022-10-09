//	2022 Metehan Tuncbilek TR, All rights reserved.

#include "PlayerAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CharacterRef = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (CharacterRef)
	{
		MeshRef = CharacterRef->GetMesh();
		MovementRef = CharacterRef->GetCharacterMovement();
	}

	DefaulAttack();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	deltaTimeX = DeltaSeconds;
	
	if (CharacterRef && MovementRef)
	{
		SetEssentialData();
		DetermineLocomotion();
	}
}


void UPlayerAnimInstance::SetEssentialData()
{
	currentSpeed = CharacterRef->GetSpeed();
	maxSpeed = MovementRef->GetMaxSpeed();
	currentAcceleration = MovementRef->GetCurrentAcceleration().Length();
	maxAcceleration = MovementRef->MaxAcceleration;
	
	aimingRotation = CharacterRef->GetAimingRotation();
	
	bIsInAir = CharacterRef->GetIsFalling();
	bHasMovementInput = CharacterRef->GetHasMovementInput();
	bIsMoving = CharacterRef->GetIsMoving();
	bShouldMove = (bHasMovementInput && bIsMoving) || currentSpeed > 150.0f;

	SetMotionStates();
}

void UPlayerAnimInstance::DetermineLocomotion()
{
	bool bInputChange = UKismetMathLibrary::Dot_VectorVector(
		UKismetMathLibrary::Normal(MovementRef->GetCurrentAcceleration()),
		UKismetMathLibrary::Normal(CharacterRef->GetVelocity())) < -0.2f;

	if (bInputChange)
	{
		LocomotionState = ELocomotionState::Idle;
	}
	else
	{
		if (CalculateThreshold(0, 560, 0.5f))
		{
			LocomotionState = ELocomotionState::Sprint;
		}
		else
		{
			if (CalculateThreshold(0, 400, 0.5f))
			{
				LocomotionState = ELocomotionState::Run;
			}
			else
			{
				if (CalculateThreshold(0, 100, 0.01f))
				{
					LocomotionState = ELocomotionState::Walk;
				}
				else
				{
					LocomotionState = ELocomotionState::Idle;
				}
			}
		}
	}
}

bool UPlayerAnimInstance::CalculateThreshold(float speed, float currentMaxSpeed, float currentMaxAcceleration)
{
	bool velocityCheck = currentSpeed > speed;
	bool maxSpeedCheck = maxSpeed > currentMaxSpeed;
	bool accelerationCheck = currentAcceleration > currentMaxAcceleration;

	return velocityCheck && maxSpeedCheck && accelerationCheck;
}

void UPlayerAnimInstance::SetMotionStates()
{
	CharacterRef->SetLocomotionState(LocomotionState);

	ActionState = CharacterRef->GetActionState();
	AbilityState = CharacterRef->GetAbilityState();
	FocusState = CharacterRef->GetFocusState();
}

void UPlayerAnimInstance::PlayMontage_Implementation(EAttackState playState)
{
	IMontagePlayer::PlayMontage_Implementation(playState);
	SetAttack(false);
	Execute_PlayMontage(this, playState);
}
void UPlayerAnimInstance::DefaulAttack()
{
	LightAttackSection = DefaultLightAttackSection;
	HeavyAttackSection = DefaultHeavyAttackSection;
}
void UPlayerAnimInstance::NextCombo(FName LightAttack, FName HeavyAttack)
{
	LightAttackSection = LightAttack;
	HeavyAttackSection = HeavyAttack;
}
void UPlayerAnimInstance::SetAttack(bool bCanAttack)
{
	CharacterRef->SetCanAttack(bCanAttack);
}
