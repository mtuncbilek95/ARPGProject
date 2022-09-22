//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SoulsProject/GameMode/MainGameMode.h"
#include "SoulsProject/World/Enemy/Base/EnemyBase.h"
#include "FightAreaBox.generated.h"

/*
 *
 *	This component was created to change Player's game mechanics. If player is in this area, both camera and player
 *	will change their states. Camera will be on higher altitude to give player more control on frustum. Player will
 *	switch to fight state which will active the combos and other expansions.
 * 
 */
UCLASS()
class SOULSPROJECT_API AFightAreaBox : public ATriggerBox
{
	GENERATED_BODY()
public:
	AFightAreaBox();

	UPROPERTY(BlueprintReadWrite, Category= "Initial Data")
	AMainGameMode* GameMode;

	//	Trigger boxes will check the enemies that are in the area.
	UFUNCTION(BlueprintCallable, Category="Data")
	void CheckEnemies(UPrimitiveComponent* OverlappedComponents);

	UFUNCTION(BlueprintCallable, Category="Data")
	void ResetEnemies(AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category="Data")
	void CheckEnemiesAtStart();
protected:
	
	UPROPERTY(EditDefaultsOnly, Category= "Data")
	TSubclassOf<AEnemyBase> EnemyType;
	UPROPERTY(EditDefaultsOnly, Category= "Data")
	TSubclassOf<APlayerCharacter> CharacterType;
	void CheckStart();
	
private:
	int EnemyCount;
};
