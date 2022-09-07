// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

//	Animation Structures
#include "SoulsProject/Character/Animation/Data/AnimData.h"

//	Interfaces which has been created to use on Combat Mechanics
#include "SoulsProject/Character/Interfaces/ComboSection.h"
#include "SoulsProject/Character/Interfaces/MontagePlayer.h"

//	Movement States that helps the animation work efficiently
#include "SoulsProject/Character/States/ActionState.h"
#include "SoulsProject/Character/States/AttackState.h"
#include "SoulsProject/Character/States/LocomotionState.h"

//	Enemy base class
#include "SoulsProject/World/Enemy/Base/EnemyBase.h"

#include "EnemyAnimInstance.generated.h"


UCLASS()
class SOULSPROJECT_API UEnemyAnimInstance : public UAnimInstance, public IMontagePlayer, public IComboSection
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

#pragma endregion 

#pragma region "Cast Data"

	UPROPERTY(BlueprintReadOnly, Category= "Base System")
	AEnemyBase* EnemyRef;

	UPROPERTY(BlueprintReadOnly, Category= "Base System")
	USkeletalMeshComponent* MeshRef;

#pragma endregion

#pragma region "Movement States"

	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	ELocomotionState LocomotionState;

	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	EActionState ActionState;

	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	EAbilityState AbilityState;
	
#pragma endregion

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

	UPROPERTY(BlueprintReadOnly, Category= "Locomotion")
	bool bAlreadyMoving;

private:
	FAnimationData IntegratedCharacterData;
};
