//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "FightAreaBox.h"

#include "Kismet/GameplayStatics.h"

AFightAreaBox::AFightAreaBox()
{
}

void AFightAreaBox::CheckEnemies(UPrimitiveComponent* OverlappedComponents)
{
	TArray<AActor*> TempArray;
	GetOverlappingActors(TempArray, CharacterType);
	
	if(TempArray.Num() > 0)
	{
		TempArray.Reset();
		OverlappedComponents->GetOverlappingActors(TempArray, EnemyType);
		EnemyCount = TempArray.Num();
		GameMode->SetAreaEnemyCount(EnemyCount);
		GameMode->CheckActionState();
	}
}

void AFightAreaBox::ResetEnemies(AActor* OtherActor)
{
	OtherActor = Cast<APlayerCharacter>(GameMode->CharacterReference);
	if(OtherActor)
	{
		GameMode->SetAreaEnemyCount(0);
		GameMode->CheckActionState();
	}
}

void AFightAreaBox::CheckEnemiesAtStart()
{
	TArray<AActor*> TempArray;
	GetOverlappingActors(TempArray, CharacterType);

	if(TempArray.Num() > 0)
	{
		TempArray.Reset();
		GetOverlappingActors(TempArray, EnemyType);
		EnemyCount = TempArray.Num();
		GameMode->SetAreaEnemyCount(EnemyCount);
		GameMode->CheckActionState();
	}
}
