// Fill out your copyright notice in the Description page of Project Settings.

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