// 2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"

enum class ENPCStates : uint8
{
	Passive		UMETA(DisplayName = "Passive"),
	Seeking		UMETA(DisplayName = "Seeking"),
	Chasing		UMETA(DisplayName = "Chasing"),
	Attacking	UMETA(DisplayName = "Attacking"),
	Defensing	UMETA(DisplayName = "Defensing")
};
