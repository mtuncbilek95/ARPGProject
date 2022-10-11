//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SoulsProject/Character/Components/HealthComponent.h"
#include "SoulsProject/GameMode/MainGameMode.h"
#include "EnemyBase.generated.h"

/*
 *
 *	This is base class for enemies. It will have specific functions in the system which allows to configurate better
 *	when developer creates a class which inheritated from this class.
 * 
 */
UCLASS()
class SOULSPROJECT_API AEnemyBase : public ACharacter, public IWeaponCollision
{
	GENERATED_BODY()

#pragma region "General Components"

public:
	// Sets default values for this character's properties
	AEnemyBase();

	UPROPERTY(BlueprintReadWrite, Category= "Initial Data")
	AMainGameMode* GameMode;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General Components")
	UStaticMeshComponent* WeaponSlot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "General Components")
	UBoxComponent* WeaponCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "General Components")
	UHealthComponent* HealthComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region "Custom Component"

public:
	UFUNCTION(Category= "Overlap Component")
	void WeaponHitOpponent(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                       bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(Category= "Overlap Component")
	void WeaponRelease(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	bool bOverlapped = false;
#pragma endregion

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

#pragma region "Locomotion Functions"

public:
	UFUNCTION(BlueprintNativeEvent, Category= "Action Functions")
	void GetHitByPlayer();

	float GetSpeed() { return GetVelocity().Length(); }
	FRotator GetAimingRotation() { return GetControlRotation(); }
	bool GetIsFalling() { return GetCharacterMovement()->IsFalling(); }
	bool GetIsMoving() { return GetSpeed() > 1.0f; }
private:
#pragma endregion

#pragma region "Action Functions"

public:
	UFUNCTION(BlueprintCallable, Category= "Attack Functions")
	void AttackTheOpponent(UAnimMontage* AnimMontage, float& length);

	virtual void ChangeCollision(bool changeValue) override;

	int debugNumber = 0;
#pragma endregion
};
