//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"

//	Basic Player Components
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

//	Enum classes for Execution Branch creation
#include "SoulsProject/Character/States/ExecutionBranches.h"

//	Movement States Enum Classes
#include "SoulsProject/Character/States/MotionStates.h"

#include "SoulsProject/Character/Weapon/WeaponActor.h"
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
	UChildActorComponent* Weapon;

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

	UFUNCTION(BlueprintCallable, Category = "Character Movement")
	void CalculateDirectionVector(FVector rotationVector);
	
private:
	void CalculateCameraLength(float speedValue);

#pragma endregion

#pragma region "Character In-Game States"
	
public:
	FORCEINLINE ELocomotionState GetLocomotionState() { return LocomotionState; }
	FORCEINLINE void SetLocomotionState(ELocomotionState stateValue) { LocomotionState = stateValue; }
	FORCEINLINE EActionState GetActionState() { return ActionState; }
	FORCEINLINE void SetActionState(EActionState stateValue) { ActionState = stateValue; }
	FORCEINLINE EAbilityState GetAbilityState() { return AbilityState; }
	FORCEINLINE void SetAbilityState(EAbilityState stateValue) { AbilityState = stateValue; }

	UFUNCTION(BlueprintPure, BlueprintCallable, Category= "Custom Functions")
	FORCEINLINE bool GetCanAttack() { return bCanAttack; }
	UFUNCTION(BlueprintCallable, Category= "Custom Functions")
	FORCEINLINE void SetCanAttack(bool attackValue) { bCanAttack = attackValue; }

private:
	ELocomotionState LocomotionState;
	EActionState ActionState = EActionState::ParkourMode;
	EAbilityState AbilityState = EAbilityState::GroundState;
	bool bCanAttack = true;

#pragma endregion

#pragma region "Custom Components"
	
public:
	UFUNCTION(BlueprintCallable, Category= "Custom Components")
	void SetWeaponActor(AWeaponActor* actor) { WeaponActor = actor; }

	UFUNCTION(BlueprintPure, BlueprintCallable, Category= "Custom Components")
	AWeaponActor* GetWeaponActor() { return WeaponActor; }

private:
	AWeaponActor* WeaponActor;

#pragma endregion
};
