// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"

#include "SoulsProject/World/Enemy/Base/EnemyBase.h"


// Sets default values
AWeaponActor::AWeaponActor()
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
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponActor::CombatOverlapping(AActor* OverlapActor)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OverlapActor);
	if(Enemy)
	{
		Enemy->EnemyHurt();
	}
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
