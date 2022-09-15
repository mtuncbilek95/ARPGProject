// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SoulsProject/Character/Animation/PlayerAnimInstance.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EnemyRef = Cast<AEnemyBase>(TryGetPawnOwner());
	if (EnemyRef)
	{
		MeshRef = EnemyRef->GetMesh();
	}
}

void UEnemyAnimInstance::PlayMontage_Implementation(EAttackState playState)
{
	IMontagePlayer::PlayMontage_Implementation(playState);
}

void UEnemyAnimInstance::DefaulAttack_Implementation()
{
	IComboSection::DefaulAttack_Implementation();
	LightAttackSection = DefaultLightAttackSection;
	HeavyAttackSection = DefaultHeavyAttackSection;
}

void UEnemyAnimInstance::NextCombo_Implementation(FName LightAttack, FName HeavyAttack)
{
	IComboSection::NextCombo_Implementation(LightAttack, HeavyAttack);

	LightAttackSection = LightAttack;
	HeavyAttackSection = HeavyAttack;
}

void UEnemyAnimInstance::SetEssentialData()
{
	if (EnemyRef)
	{
		IntegratedCharacterData.currentVelocity = EnemyRef->GetVelocity();
		IntegratedCharacterData.vCurrentAcceleration = EnemyRef->GetCharacterMovement()->GetCurrentAcceleration();
		IntegratedCharacterData.currentLastInput = EnemyRef->GetLastMovementInputVector();
		IntegratedCharacterData.currentMaxSpeed = EnemyRef->GetCharacterMovement()->GetMaxSpeed();
		IntegratedCharacterData.currentSpeed = IntegratedCharacterData.currentVelocity.Size();
		IntegratedCharacterData.fCurrentAcceleration = IntegratedCharacterData.vCurrentAcceleration.Size();

		EnemyRef->LocomotionState = LocomotionState;
		ActionState = EnemyRef->ActionState;
		AbilityState = EnemyRef->AbilityState;
	}

}

void UEnemyAnimInstance::DetermineLocomotion()
{
	if (IntegratedCharacterData.currentVelocity.Length() > 400)
	{
		LocomotionState = ELocomotionState::Run;
	}
	else if (IntegratedCharacterData.currentVelocity.Length() > 50 && IntegratedCharacterData.currentVelocity.Length() < 400)
	{
		LocomotionState = ELocomotionState::Walk;
	}
	else
	{
		LocomotionState = ELocomotionState::Idle;
	}
}
