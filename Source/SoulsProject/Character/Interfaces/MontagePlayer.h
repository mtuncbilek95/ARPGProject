﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoulsProject/Character/States/AttackState.h"
#include "UObject/Interface.h"
#include "MontagePlayer.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMontagePlayer : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOULSPROJECT_API IMontagePlayer
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayMontage(EAttackState playState);
};
