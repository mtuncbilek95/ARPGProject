// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EExecuteBranch : uint8
{
	Pressed		UMETA(DisplayName = "Pressed"),
	Released	UMETA(DisplayName = "Released")
};

UENUM(BlueprintType)
enum class EOverlap : uint8
{
	BeginOverlap	UMETA(DisplayName = "Turn"),
	EndOverlap		UMETA(DisplayName = "LookUp")
};