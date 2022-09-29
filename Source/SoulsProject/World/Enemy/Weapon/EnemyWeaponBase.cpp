// 2022 Metehan Tuncbilek TR, All rights reserved.


#include "EnemyWeaponBase.h"


// Sets default values
AEnemyWeaponBase::AEnemyWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

