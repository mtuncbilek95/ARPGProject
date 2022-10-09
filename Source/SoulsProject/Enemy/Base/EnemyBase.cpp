//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "EnemyBase.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	WeaponSlot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Weapon"));
	WeaponSlot->SetupAttachment(GetMesh(), "ik_hand_gun");
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collision"));
	WeaponCollision->SetupAttachment(WeaponSlot);
}

void AEnemyBase::ChangeCollision(bool valueCollision)
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

void AEnemyBase::WeaponHitOpponent(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if(Player)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, "Player got hurt");
		Player->GetHitByEnemy();
	}
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if(WeaponCollision)
	{
		WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::WeaponHitOpponent);
	}
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::AttackTheOpponent(UAnimMontage* AnimMontage, float& length)
{
	PlayAnimMontage(AnimMontage);
	length = AnimMontage->GetPlayLength();
}

void AEnemyBase::GetHitByPlayer_Implementation()
{
}
