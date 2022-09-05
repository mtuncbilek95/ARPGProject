// Copyright Epic Games, Inc. All Rights Reserved.


#include "MainGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "SoulsProject/Character/States/ActionState.h"

AMainGameMode::AMainGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMainGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMainGameMode::CheckActionState()
{
	UE_LOG(LogTemp, Warning, TEXT("%zu"), enemyCount)
	if(enemyCount != 0)
	{
		CharacterReference->SetActionState(EActionState::FightMode);
	}
	else
	{
		CharacterReference->SetActionState(EActionState::ParkourMode);
	}
}

void AMainGameMode::SetAreaEnemyCount(int countValue)
{
	enemyCount = countValue;
}
