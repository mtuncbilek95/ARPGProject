// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SoulsProject/GameMode/MainGameMode.h"
#include "EnemyBase.generated.h"

/*
 *
 *	This is base class for enemies. It will have specific functions in the system which allows to configurate better
 *	when developer creates a class which inheritated from this class.
 * 
 */
UCLASS()
class SOULSPROJECT_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	UPROPERTY(BlueprintReadWrite, Category= "Initial Data")
	AMainGameMode* GameMode;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void EnemyHurt();

	UPROPERTY(BlueprintReadOnly, Category="Annen")
	int Health = 10;
private:

};
