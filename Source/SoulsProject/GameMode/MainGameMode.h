//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SoulsProject/Character/Player/PlayerCharacter.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SOULSPROJECT_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMainGameMode();
	
	void SetAreaEnemyCount(int countValue);

	UPROPERTY(BlueprintReadWrite, Category="Initial Data")
	APlayerCharacter* CharacterReference;

	void CheckActionState();
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	int enemyCount;
	
};
