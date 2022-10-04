//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include <imgui.h>

//	Basic Player Components
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

//	Enum classes for Execution Branch creation
#include "SoulsProject/Character/States/ExecutionBranches.h"

//	Movement States Enum Classes
#include "SoulsProject/Character/States/MotionStates.h"

#include "SoulsProject/Character/Weapon/PlayerWeaponBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SOULSPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region "Main Component"

public:
	//	Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Character Component")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Character Component")
	UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Character Component")
	UChildActorComponent* WeaponSlot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region "General Functions"

public:
	UFUNCTION(BlueprintCallable, Category = "Character Movement", Meta = (ExpandEnumAsExecs = "Branches"))
	void Sprint(EExecuteBranch Branches);
	UFUNCTION(BlueprintCallable, Category = "Character Movement", Meta = (ExpandEnumAsExecs = "Branches"))
	void Walk(EExecuteBranch Branches);
	UFUNCTION(BlueprintCallable, Category= "Character Movement")
	void MoveCharacter(float forwardInput, float rightInput);
	UFUNCTION(BlueprintCallable, Category = "Character Movement")
	void RotateCharacter(float axisTurn, float axisLook);

private:
	void CalculateCameraLength(float speedValue);

#pragma endregion

#pragma region "Enemy Lock System"

public:
	UFUNCTION(BlueprintCallable, Category = "Character Movement")
	FVector CalculateDirectionVector();
	UFUNCTION(BlueprintCallable, Category= "Ray-casting Data")
	void HardLockTrace();
	UFUNCTION(BlueprintCallable, Category= "Ray-casting Data")
	void SoftLockTrace();
	UFUNCTION(BlueprintCallable, Category= "Ray-casting Data")
	void HardLock();
	UFUNCTION(BlueprintCallable, Category = "Ray-casting Data")
	void LockOnTarget();
	UFUNCTION(BlueprintCallable, Category= "Ray-casting Data")
	void LockingProps(bool bIsPlayerLocked);
	UFUNCTION(BlueprintPure, BlueprintCallable, Category= "Ray-casting Data")
	FHitResult GetHitResult() { return LockHitResult; }

	void SetSphereRad(float valueRad) { sphereRadius = valueRad; }
	void SetSphereLength(float valueLength) { sphereLength = valueLength; }
	void SetInterpSpeed(float valueInterp) { interpSpeed = valueInterp; }
private:
	AActor* hitActor;
	FTimerHandle LockTimerHandle;
	FHitResult LockHitResult;
	float sphereLength = 1000;
	float sphereRadius = 100;
	float interpSpeed = 0.2f;
#pragma endregion

#pragma region "Character In-Game States"

public:
	FORCEINLINE ELocomotionState GetLocomotionState() { return LocomotionState; }
	FORCEINLINE void SetLocomotionState(ELocomotionState stateValue) { LocomotionState = stateValue; }
	FORCEINLINE EActionState GetActionState() { return ActionState; }
	FORCEINLINE void SetActionState(EActionState stateValue) { ActionState = stateValue; }
	FORCEINLINE EAbilityState GetAbilityState() { return AbilityState; }
	FORCEINLINE void SetAbilityState(EAbilityState stateValue) { AbilityState = stateValue; }
	FORCEINLINE EFocusState GetFocusState() { return FocusState; }
	FORCEINLINE void SetFocusState(EFocusState stateValue) { FocusState = stateValue; }

	UFUNCTION(BlueprintPure, BlueprintCallable, Category= "Custom Functions")
	FORCEINLINE bool GetCanAttack() { return bCanAttack; }
	UFUNCTION(BlueprintCallable, Category= "Custom Functions")
	FORCEINLINE void SetCanAttack(bool attackValue) { bCanAttack = attackValue; }

private:
	ELocomotionState LocomotionState;
	EActionState ActionState = EActionState::FightMode;
	EAbilityState AbilityState = EAbilityState::GroundState;
	EFocusState FocusState = EFocusState::FreeState;
	bool bCanAttack = true;

#pragma endregion

#pragma region "Custom Components Property"

public:
	UFUNCTION(BlueprintCallable, Category= "Custom Components")
	void SetWeaponActor(APlayerWeaponBase* playerActor) { WeaponActor = playerActor; }
	
	UFUNCTION(BlueprintPure, BlueprintCallable, Category= "Custom Components")
	APlayerWeaponBase* GetWeaponActor() { return WeaponActor; }

private:
	APlayerWeaponBase* WeaponActor;

#pragma endregion

#pragma region "Action Functions"

public:
	UFUNCTION(BlueprintNativeEvent, Category= "Action Functions")
	void GetHitByEnemy();

#pragma endregion 
};
