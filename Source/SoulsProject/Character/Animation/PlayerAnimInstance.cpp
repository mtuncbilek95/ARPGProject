// Fill out your copyright notice in the Description page of Project Settings.

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
	}
}

void UPlayerAnimInstance::PlayMontage_Implementation(EAttackState playState)
{
	IMontagePlayer::PlayMontage_Implementation(playState);
	AttackSetter(false);
}

void UPlayerAnimInstance::DefaulAttack_Implementation()
{
	IComboSection::DefaulAttack_Implementation();
	LightAttackSection = DefaultLightAttackSection;
	HeavyAttackSection = DefaultHeavyAttackSection;
}

void UPlayerAnimInstance::NextCombo_Implementation(FName LightAttack, FName HeavyAttack)
{
	IComboSection::NextCombo_Implementation(LightAttack, HeavyAttack);

	LightAttackSection = LightAttack;
	HeavyAttackSection = HeavyAttack;
}

void UPlayerAnimInstance::AttackSetter_Implementation(bool bCanAttack)
{
	IMontagePlayer::AttackSetter_Implementation(bCanAttack);
	CharacterRef->SetAttack(bCanAttack);
}

void UPlayerAnimInstance::GetCombatRotation_Implementation()
{
	IComboSection::GetCombatRotation_Implementation();

	combatRotation = CharacterRef->inputForcedRotation;
}

void UPlayerAnimInstance::SetCombatRotation_Implementation()
{
	IComboSection::SetCombatRotation_Implementation();

	CharacterRef->SetActorRotation(
		UKismetMathLibrary::RInterpTo(CharacterRef->GetActorRotation(), combatRotation, GetWorld()->GetDeltaSeconds(),
		                              25));
}

void UPlayerAnimInstance::SetEssentialData()
{
	if (CharacterRef)
	{
		IntegratedCharacterData.currentVelocity = CharacterRef->GetVelocity();
		IntegratedCharacterData.vCurrentAcceleration = CharacterRef->GetCharacterMovement()->GetCurrentAcceleration();
		IntegratedCharacterData.currentLastInput = CharacterRef->GetLastMovementInputVector();
		IntegratedCharacterData.currentMaxSpeed = CharacterRef->GetCharacterMovement()->GetMaxSpeed();
		IntegratedCharacterData.currentSpeed = IntegratedCharacterData.currentVelocity.Size();
		IntegratedCharacterData.fCurrentAcceleration = IntegratedCharacterData.vCurrentAcceleration.Size();

		fVec = CharacterRef->forwardAxis;
		rVec = CharacterRef->rightAxis;

		CharacterRef->LocomotionState = LocomotionState;
		ActionState = CharacterRef->ActionState;
		AbilityState = CharacterRef->AbilityState;
		bAlreadyMoving = IntegratedCharacterData.currentSpeed > 50;
	}
}

void UPlayerAnimInstance::DetermineLocomotion()
{
	bool bInputChange = UKismetMathLibrary::Dot_VectorVector(
		UKismetMathLibrary::Normal(IntegratedCharacterData.vCurrentAcceleration),
		UKismetMathLibrary::Normal(IntegratedCharacterData.currentVelocity)) < -0.2f;

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

bool UPlayerAnimInstance::CalculateThreshold(float speed, float maxSpeed, float maxAcceleration)
{
	bool velocityCheck = IntegratedCharacterData.currentSpeed > speed;
	bool maxSpeedCheck = IntegratedCharacterData.currentMaxSpeed > maxSpeed;
	bool accelerationCheck = IntegratedCharacterData.fCurrentAcceleration > maxAcceleration;

	return velocityCheck && maxSpeedCheck && accelerationCheck;
}
