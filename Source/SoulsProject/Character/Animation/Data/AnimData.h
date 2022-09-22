//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimData.generated.h"

USTRUCT(BlueprintType)
struct FAnimationData
{
	GENERATED_BODY()
	
public:
	FVector currentVelocity;
	FVector vCurrentAcceleration;
	FVector currentLastInput;
	float currentMaxSpeed;
	float currentSpeed;
	float fCurrentAcceleration;
};