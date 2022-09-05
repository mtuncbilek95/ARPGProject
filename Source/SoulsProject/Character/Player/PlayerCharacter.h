// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SoulsProject/Character/States/ExecuteBranch.h"
#include "SoulsProject/Character/States/LocomotionState.h"
#include "SoulsProject/Character/States/ActionState.h"
#include "SoulsProject/Character/States/AbilityState.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SOULSPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

#pragma region "Main Component"

	UPROPERTY(EditDefaultsOnly, Category= "Character Component")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, Category= "Character Component")
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

	UPROPERTY(EditDefaultsOnly, Category= "Character Component")
	float interpSpeed;

	UPROPERTY(BlueprintReadWrite, Category= "Locomotion")
	bool bCanAttack = true;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region "Axis Functions"
	
	UFUNCTION(BlueprintCallable, Category= "Character Movement")
	void MoveCharacter(float forwardAxis, float rightAxis);

	UFUNCTION(BlueprintCallable, Category = "Character Movement")
	void RotateCharacter(float axisTurn, float axisLook);

#pragma endregion 

#pragma region "Action Functions"

	UFUNCTION(BlueprintCallable, Category = "Character Movement", Meta = (ExpandEnumAsExecs = "Branches"))
	void Sprint(EExecuteBranch Branches);

	UFUNCTION(BlueprintCallable, Category = "Character Movement", Meta = (ExpandEnumAsExecs = "Branches"))
	void Walk(EExecuteBranch Branches);

#pragma endregion
	
	void SetActionState(EActionState currentState);

private:
	
	void CalculateCameraLength(float speedValue);
};
