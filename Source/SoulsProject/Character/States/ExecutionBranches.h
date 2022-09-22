//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"

//	This branch is used for handling action binding events
UENUM(BlueprintType)
enum class EExecuteBranch : uint8
{
	Pressed		UMETA(DisplayName = "Pressed"),
	Released	UMETA(DisplayName = "Released")
};

//	This branch is used for Collision overlap events
UENUM(BlueprintType)
enum class EOverlap : uint8
{
	BeginOverlap	UMETA(DisplayName = "Turn"),
	EndOverlap		UMETA(DisplayName = "LookUp")
};

//	Custom branch idea.
UENUM(BlueprintType)
enum class EEnterBranch : uint8
{
	Enter		UMETA(DisplayName = "Enter"),
	Reset		UMETA(DisplayName = "Exit")
};