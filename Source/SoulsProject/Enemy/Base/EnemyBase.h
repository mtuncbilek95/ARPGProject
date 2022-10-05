﻿//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SoulsProject/GameMode/MainGameMode.h"
#include "EnemyBase.generated.h"

/*
 *
 *	This is base class for enemies. It will have specific functions in the system which allows to configurate better
 *	when developer creates a class which inheritated from this class.
 * 
 */
UCLASS()
class SOULSPROJECT_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

#pragma region "General Components"
	
public:
	// Sets default values for this character's properties
	AEnemyBase();

	UPROPERTY(BlueprintReadWrite, Category= "Initial Data")
	AMainGameMode* GameMode;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom Component")
	UStaticMeshComponent* WeaponSlot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Custom Component")
	UBoxComponent* WeaponCollision;
#pragma endregion

#pragma region "Custom Component"
	
public:
	UFUNCTION(BlueprintCallable, Category= "Custom Component")
	void ChangeCollision(bool valueCollision);
	UFUNCTION(BlueprintCallable, Category= "Custom Component")
	void CombatOverlapping(AActor* OverlapActor);

#pragma endregion 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region "Character In-Game States"
	
public:
	FORCEINLINE ELocomotionState GetLocomotionState() { return LocomotionState; }
	FORCEINLINE void SetLocomotionState(ELocomotionState stateValue) { LocomotionState = stateValue; }
	FORCEINLINE EActionState GetActionState() { return ActionState; }
	FORCEINLINE void SetActionState(EActionState stateValue) { ActionState = stateValue; }
	FORCEINLINE EAbilityState GetAbilityState() { return AbilityState; }
	FORCEINLINE void SetAbilityState(EAbilityState stateValue) { AbilityState = stateValue; }
	
private:
	ELocomotionState LocomotionState;
	EActionState ActionState = EActionState::ParkourMode;
	EAbilityState AbilityState = EAbilityState::GroundState;

#pragma endregion

#pragma region "Action Functions"
	
public:
	UFUNCTION(BlueprintPure, BlueprintCallable, Category= "Action Functions")
	bool GetCanAttack() { return bCanAttack; }
	UFUNCTION(BlueprintCallable, Category= "Action Functions")
	void SetCanAttack(bool attackValue) { bCanAttack = attackValue; }

	UFUNCTION(BlueprintNativeEvent, Category= "Action Functions")
	void GetHitByPlayer();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category= "Action Functions")
	void Attack(UAnimMontage* Montage, float& length);
private:
	bool bCanAttack = true;

#pragma endregion
};
