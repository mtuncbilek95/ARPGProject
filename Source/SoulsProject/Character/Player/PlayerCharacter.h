// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//	Basic Player Components
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

//	Interfaces
#include "SoulsProject/Character/Interfaces/WeaponCollider.h"

//	Enum classes for Execution Branch creation
#include "SoulsProject/Character/States/ExecuteBranch.h"

//	Movement States Enum Classes
#include "SoulsProject/Character/States/LocomotionState.h"
#include "SoulsProject/Character/States/ActionState.h"
#include "SoulsProject/Character/States/AbilityState.h"
#include "SoulsProject/Character/Weapon/WeaponActor.h"
#include "PlayerCharacter.generated.h"

class AEnemyBase;

UCLASS()
class SOULSPROJECT_API APlayerCharacter : public ACharacter, public IWeaponCollider
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

#pragma region "Main Component"

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Character Component")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Character Component")
	UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Character Component")
	UChildActorComponent* Weapon;

#pragma endregion

#pragma region "Character In-Game States"

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category= "Character Component")
	ELocomotionState LocomotionState;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category= "Character Component")
	EActionState ActionState = EActionState::ParkourMode;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category= "Character Component")
	EAbilityState AbilityState = EAbilityState::GroundState;

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Focus Target")
	void FocusOnTarget();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Focus Target", meta=(ExpandEnumAsExecs = "ExecuteBranch"))
	void CastTrace(EEnterBranch ExecuteBranch);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Focus Target")
	TEnumAsByte<EObjectTypeQuery> QueryType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon")
	AEnemyBase* EnemyRef;
	
	UPROPERTY(EditDefaultsOnly, Category= "Character Component")
	float interpSpeed;

	UPROPERTY(BlueprintReadWrite, Category= "Locomotion")
	bool bCanAttack = true;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region "Axis Functions"
	
	UFUNCTION(BlueprintCallable, Category= "Character Movement")
	void MoveCharacter(float forwardInput, float rightInput);

	UFUNCTION(BlueprintCallable, Category = "Character Movement")
	void RotateCharacter(float axisTurn, float axisLook);

#pragma endregion 

#pragma region "Action Functions"

	UFUNCTION(BlueprintCallable, Category = "Character Movement", Meta = (ExpandEnumAsExecs = "Branches"))
	void Sprint(EExecuteBranch Branches);

	UFUNCTION(BlueprintCallable, Category = "Character Movement", Meta = (ExpandEnumAsExecs = "Branches"))
	void Walk(EExecuteBranch Branches);

#pragma endregion

#pragma region "Interface Functions"

virtual void ChangeWeaponCollider_Implementation(bool bColliderActive) override;

#pragma endregion
	
	void SetActionState(EActionState currentState);

	void SetAttack(bool value);

	int forwardAxis;
	int rightAxis;

	UPROPERTY(BlueprintReadWrite)
	FRotator inputForcedRotation;
	
private:
	void CalculateCameraLength(float speedValue);
	void CalculateForcedDirection(float forwardValue, float rightValue);
};
