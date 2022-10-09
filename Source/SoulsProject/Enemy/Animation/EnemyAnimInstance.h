//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

//	Interfaces which has been created to use on Combat Mechanics
#include "SoulsProject/Character/Interfaces/ComboSection.h"
#include "SoulsProject/Character/Interfaces/MontagePlayer.h"

//	Movement States that helps the animation work efficiently
#include "SoulsProject/Character/States/MotionStates.h"

//	Enemy base class
#include "SoulsProject/Enemy/Base/EnemyBase.h"

#include "EnemyAnimInstance.generated.h"


UCLASS()
class SOULSPROJECT_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

#pragma region "Movement States"

public:
	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	ELocomotionState LocomotionState;
	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	EActionState ActionState;
	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	EAbilityState AbilityState;

	void SetMotionStates();
	void SetEssentialData();
	void DetermineLocomotion();
private:
	float currentSpeed, maxSpeed, currentAcceleration, maxAcceleration;
	FRotator aimingRotation;

	bool bIsInAir, bIsMoving, bShouldMove;

	float deltaTimeX;

#pragma endregion

#pragma region "Cast Data"
	
private:
	UPROPERTY()
	AEnemyBase* CharacterRef;
	UPROPERTY()
	UCharacterMovementComponent* MovementRef;
	UPROPERTY()
	USkeletalMeshComponent* MeshRef;

#pragma endregion
};
