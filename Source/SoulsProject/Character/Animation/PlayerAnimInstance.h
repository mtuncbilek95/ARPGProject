//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "SoulsProject/Character/Interfaces/ComboSection.h"
#include "SoulsProject/Character/Interfaces/MontagePlayer.h"
#include "SoulsProject/Character/Player/PlayerCharacter.h"

#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULSPROJECT_API UPlayerAnimInstance : public UAnimInstance, public IMontagePlayer, public IComboSection
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


#pragma region "Interface Functions"

public:
	virtual void PlayMontage_Implementation(EAttackState playState) override;
	virtual void DefaulAttack() override;
	virtual void NextCombo(FName LightAttack, FName HeavyAttack) override;
	UFUNCTION(BlueprintCallable, Category= "Interfaces")
	virtual void SetAttack(bool bCanAttack) override;


#pragma endregion

#pragma region "Cast Data"

protected:
	UPROPERTY(BlueprintReadOnly, Category= "Base System")
	APlayerCharacter* CharacterRef;
	UPROPERTY(BlueprintReadOnly, Category= "Base System")
	USkeletalMeshComponent* MeshRef;
	UPROPERTY(BlueprintReadOnly, Category= "Base System")
	UCharacterMovementComponent* MovementRef;

#pragma endregion

#pragma region "Locomotion States & Functions"

protected:
	UPROPERTY(BlueprintReadOnly, Category= "Locomotion States")
	ELocomotionState LocomotionState;
	UPROPERTY(BlueprintReadOnly, Category= "Locomotion States")
	EActionState ActionState;
	UPROPERTY(BlueprintReadOnly, Category= "Locomotion States")
	EAbilityState AbilityState;
	UPROPERTY(BlueprintReadOnly, Category= "Locomotion States")
	EFocusState FocusState;

private:
	void DetermineLocomotion();
	void SetMotionStates();

	bool CalculateThreshold(float currentSpeed, float currentMaxSpeed, float currentMaxAcceleration);

#pragma endregion

#pragma region "Essential Data"

protected:
	void SetEssentialData();

private:
	bool bIsInAir, bShouldMove, bHasMovementInput, bIsMoving;

	float currentSpeed, maxSpeed, currentAcceleration, maxAcceleration;
	float inputLR, inputFB;
	float deltaTimeX, aimYawRate;
	FRotator aimingRotation;
	
#pragma endregion

#pragma region "Combo Section Data"

public:
	UPROPERTY(BlueprintReadWrite, Category= "Combo Mechanics")
	FName LightAttackSection;
	UPROPERTY(BlueprintReadWrite, Category= "Combo Mechanics")
	FName HeavyAttackSection;
	UPROPERTY(BlueprintReadWrite, Category= "Combo Mechanics")
	FName DefaultLightAttackSection = "LightStandart1";
	UPROPERTY(BlueprintReadWrite, Category= "Combo Mechanics")
	FName DefaultHeavyAttackSection = "HeavyStandart1";

#pragma endregion
	
};
