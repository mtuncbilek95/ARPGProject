// 2022 Metehan Tuncbilek TR, All rights reserved.


#include "EnemyWeaponBase.h"

#include "SoulsProject/Character/Player/PlayerCharacter.h"


// Sets default values
AEnemyWeaponBase::AEnemyWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene"));
	RootComponent = SceneComponent;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collision"));
	WeaponCollision->SetupAttachment(WeaponMesh);

	WeaponMesh->SetRelativeRotation(FRotator(0, 0, 0));
	WeaponCollision->SetBoxExtent(FVector(2, 1, 43));
	WeaponCollision->SetRelativeLocation(FVector(0, 0, 60));

	WeaponCollision->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void AEnemyWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyWeaponBase::CombatOverlapping(AActor* OverlapActor)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OverlapActor);
	if(Player)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, "Player got hurt");
		Player->GetHitByEnemy();
	}
}

void AEnemyWeaponBase::ChangeCollision(bool valueCollision)
{
	if(valueCollision)
	{
		WeaponCollision->SetCollisionProfileName("Weapon");
	}
	else
	{
		WeaponCollision->SetCollisionProfileName("NoCollision");
	}
}