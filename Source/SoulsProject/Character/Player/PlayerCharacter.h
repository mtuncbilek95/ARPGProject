//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"

//	Basic Player Components
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"

//	Enum classes for Execution Branch creation
#include "SoulsProject/Character/States/ExecutionBranches.h"

//	Movement States Enum Classes
#include "SoulsProject/Character/Components/HealthComponent.h"
#include "SoulsProject/Character/States/MotionStates.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SOULSPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

#pragma region "Main Component"

public:
	//	Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Character Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Character Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Character Components")
	UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Character Components")
	UStaticMeshComponent* VisionPlane;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Character Components")
	UStaticMeshComponent* WeaponSlot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Character Components")
	USceneComponent* WeaponB;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Character Components")
	USceneComponent* WeaponT;
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
	void SetupSpringArm();
	void SetupCamera();
	void SetupWeapon();
	void SetupCharacter();
	void CalculateCameraLength(float speedValue);

#pragma endregion

#pragma region "Enemy Lock System"

public:
	UFUNCTION(BlueprintCallable, Category = "Enemy Lock System")
	FVector CalculateDirectionVector();
	UFUNCTION(BlueprintCallable, Category= "Enemy Lock System")
	void HardLockTrace();
	UFUNCTION(BlueprintCallable, Category= "Enemy Lock System")
	void SoftLockTrace();
	UFUNCTION(BlueprintCallable, Category= "Enemy Lock System")
	void HardLock();
	UFUNCTION(BlueprintCallable, Category = "Enemy Lock System")
	void LockOnTarget();
	UFUNCTION(BlueprintCallable, Category= "Enemy Lock System")
	void LockingProps(bool bIsPlayerLocked);

	void SetSphereRad(float valueRad);
	void SetSphereLength(float valueLength);
	void SetInterpSpeed(float valueInterp);

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
	FORCEINLINE ELocomotionState GetLocomotionState();
	FORCEINLINE void SetLocomotionState(ELocomotionState stateValue);
	FORCEINLINE EActionState GetActionState();
	FORCEINLINE void SetActionState(EActionState stateValue);
	FORCEINLINE EAbilityState GetAbilityState();
	FORCEINLINE void SetAbilityState(EAbilityState stateValue);
	FORCEINLINE EFocusState GetFocusState();
	FORCEINLINE void SetFocusState(EFocusState stateValue);
	UFUNCTION(BlueprintPure, BlueprintCallable, Category= "Custom Functions")
	FORCEINLINE bool GetCanAttack();
	UFUNCTION(BlueprintCallable, Category= "Custom Functions")
	FORCEINLINE void SetCanAttack(bool attackValue);

private:
	ELocomotionState LocomotionState;
	EActionState ActionState = EActionState::FightMode;
	EAbilityState AbilityState = EAbilityState::GroundState;
	EFocusState FocusState = EFocusState::FreeState;
	bool bCanAttack = true;
	FVector NextTop, FirstTop, NextBot, FirstBot;
#pragma endregion

#pragma region "Action Functions"

public:
	UFUNCTION(BlueprintNativeEvent, Category= "Action Functions")
	void GetHitByEnemy();
	UFUNCTION(Category= "Overlap Component")
	void WeaponHitOpponent(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                       bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, Category=" Action Functions")
	void PlayerAttack(EAttackState playState);

	void TraceWeapon();
	bool bCanActiveTrace;
private:
	bool bWeaponOverlapped = false;
	float deltaTime;

#pragma endregion

#pragma region "Locomotion Functions"

public:
	bool GetIsFalling();
	bool GetHasMovementInput();
	bool GetIsMoving();
	float GetSpeed();

	FRotator GetAimingRotation();

#pragma endregion

#pragma region "Life Functions"

public:
	UFUNCTION()
	void Execute_TakeDamage();

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* A;
private:
#pragma endregion
};
