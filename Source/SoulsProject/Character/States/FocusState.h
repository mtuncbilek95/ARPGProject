// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FFocusState : uint8
{
	FreeState	UMETA(DisplayName = "FreeState"),
	FocusState	UMETA(DisplayName = "FocusState")
};