//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "EnemyBase.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"


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

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->RegisterComponent();
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::WeaponHitOpponent);
	WeaponCollision->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::WeaponRelease);
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::ChangeCollision(bool valueCollision)
{
	if (valueCollision)
	{
		WeaponCollision->SetCollisionProfileName("Weapon");
	}
	else
	{
		WeaponCollision->SetCollisionProfileName("NoCollision");
	}
}

void AEnemyBase::WeaponHitOpponent(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
                                   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TSubclassOf<UDamageType> dmgType;
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		debugNumber ++;
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, ("Hit " + UKismetStringLibrary::Conv_IntToString(debugNumber)));
		UGameplayStatics::ApplyDamage(Player, FMath::RandRange(10,15),GetController(),this, dmgType);
	}
}

void AEnemyBase::WeaponRelease(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AEnemyBase::AttackTheOpponent(UAnimMontage* AnimMontage, float& length)
{
	PlayAnimMontage(AnimMontage);
	length = AnimMontage->GetPlayLength();
}

void AEnemyBase::GetHitByPlayer_Implementation()
{
}
