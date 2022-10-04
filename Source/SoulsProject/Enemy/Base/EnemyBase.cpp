//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "EnemyBase.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));

	WeaponSlot = CreateDefaultSubobject<UChildActorComponent>(TEXT("EnemyWeapon"));
	WeaponSlot->SetupAttachment(GetMesh(), "ik_hand_gun");
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::GetHitByPlayer_Implementation()
{
}
