//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/AnimData.h"

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

public:
	UFUNCTION(BlueprintCallable, Category= "Locomotion")
	void SetEssentialData();
	UFUNCTION(BlueprintCallable, Category= "Locomotion")
	void DetermineLocomotion();

protected:
	virtual void NativeInitializeAnimation() override;

#pragma region "Interface Functions"

	virtual void PlayMontage_Implementation(EAttackState playState) override;

	virtual void DefaulAttack_Implementation() override;

	virtual void NextCombo_Implementation(FName LightAttack, FName HeavyAttack) override;

	virtual void AttackSetter_Implementation(bool bCanAttack) override;

#pragma endregion

#pragma region "Cast Data"

	UPROPERTY(BlueprintReadOnly, Category= "Base System")
	APlayerCharacter* CharacterRef;

	UPROPERTY(BlueprintReadOnly, Category= "Base System")
	USkeletalMeshComponent* MeshRef;

#pragma endregion

	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	ELocomotionState LocomotionState;

	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	EActionState ActionState;

	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	EAbilityState AbilityState;

	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	bool bAlreadyMoving;

#pragma region "Combo Section Data"

	UPROPERTY(BlueprintReadWrite, Category= "Combo Mechanics")
	FName LightAttackSection;

	UPROPERTY(BlueprintReadWrite, Category= "Combo Mechanics")
	FName HeavyAttackSection;

	UPROPERTY(BlueprintReadWrite, Category= "Combo Mechanics")
	FName DefaultLightAttackSection = "Light1";

	UPROPERTY(BlueprintReadWrite, Category= "Combo Mechanics")
	FName DefaultHeavyAttackSection = "Heavy1";

#pragma endregion

private:
	FAnimationData IntegratedCharacterData;

	bool CalculateThreshold(float currentSpeed, float maxSpeed, float maxAcceleration);
};
