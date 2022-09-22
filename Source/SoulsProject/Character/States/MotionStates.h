//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"

//	Locomotion states
UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA(DisplayName = "Run"),
	Sprint UMETA(DisplayName = "Sprint")
};

//	State that determines if player focused on an enemy or not.
UENUM(BlueprintType)
enum class FFocusState : uint8
{
	FreeState	UMETA(DisplayName = "FreeState"),
	FocusState	UMETA(DisplayName = "FocusState")
};

//	State that determines montage mechanics when using the related event.
UENUM(BlueprintType)
enum class EAttackState : uint8
{
	LightAttack,
	HeavyAttack,
	AirAttack
};

//	This state change player character's behaviour according to player's surroundings.
UENUM(BlueprintType)
enum class EActionState : uint8
{
	FightMode,
	ParkourMode
};

/*
 *	This state helps montage player to determine if player is on ground or in air, which eventually change
 *	both parkour states and combat states.
 */
UENUM(BlueprintType)
enum class EAbilityState : uint8
{
	GroundState,
	InAirState
};