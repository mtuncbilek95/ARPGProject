//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "EnemyAnimInstance.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CharacterRef = Cast<AEnemyBase>(TryGetPawnOwner());

	if(CharacterRef)
	{
		MeshRef = CharacterRef->GetMesh();
		MovementRef = CharacterRef->GetCharacterMovement();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	deltaTimeX = DeltaSeconds;

	if(CharacterRef)
	{
		SetEssentialData();
		DetermineLocomotion();
	}
}

void UEnemyAnimInstance::SetMotionStates()
{
	CharacterRef->SetLocomotionState(LocomotionState);
	AbilityState = CharacterRef->GetAbilityState();
	ActionState = CharacterRef->GetActionState();
}

void UEnemyAnimInstance::SetEssentialData()
{
	currentSpeed = CharacterRef->GetSpeed();
	maxSpeed = MovementRef->GetMaxSpeed();
	currentAcceleration = MovementRef->GetCurrentAcceleration().Length();
	maxAcceleration = MovementRef->MaxAcceleration;
	
	aimingRotation = CharacterRef->GetAimingRotation();
	
	bIsInAir = CharacterRef->GetIsFalling();
	bIsMoving = CharacterRef->GetIsMoving();
	bShouldMove = bIsMoving || currentSpeed > 150.0f;

	SetMotionStates();
}

void UEnemyAnimInstance::DetermineLocomotion()
{
	if(currentSpeed > 300)
	{
		LocomotionState = ELocomotionState::Run;
	}
	else if(currentSpeed > 50 && currentSpeed < 300)
	{
		LocomotionState = ELocomotionState::Walk;
	}
	else
	{
		LocomotionState = ELocomotionState::Idle;
	}
}
