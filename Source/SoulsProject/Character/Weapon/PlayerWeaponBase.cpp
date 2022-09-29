//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "PlayerWeaponBase.h"

#include "SoulsProject/World/Enemy/Base/EnemyBase.h"


// Sets default values
APlayerWeaponBase::APlayerWeaponBase()
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
void APlayerWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerWeaponBase::CombatOverlapping(AActor* OverlapActor)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OverlapActor);
	if(Enemy)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, "Enemy got hurt");
	}
}

// Called every frame
void APlayerWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerWeaponBase::ChangeCollision(bool value)
{
	if(value)
	{
		WeaponCollision->SetCollisionProfileName("Weapon");
	}
	else
	{
		WeaponCollision->SetCollisionProfileName("NoCollision");
	}
}

