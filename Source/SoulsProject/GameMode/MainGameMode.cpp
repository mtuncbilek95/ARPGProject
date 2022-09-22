//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "MainGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

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
