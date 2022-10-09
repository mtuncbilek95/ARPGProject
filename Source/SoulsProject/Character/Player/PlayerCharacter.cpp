//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SoulsProject/Character/Interfaces/MontagePlayer.h"
#include "SoulsProject/Enemy/Base/EnemyBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupSpringArm();
	SetupCamera();
	SetupCharacter();
	SetupWeapon();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(WeaponCollision)
	{
		WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::WeaponHitOpponent);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::Sprint(EExecuteBranch Branches)
{
	if(FocusState == EFocusState::FreeState)
	{
		switch (Branches)
		{
		case EExecuteBranch::Pressed:
			if (LocomotionState != ELocomotionState::Walk)
			{
				GetCharacterMovement()->MaxWalkSpeed = 620;
			}
			break;
		case EExecuteBranch::Released:
			GetCharacterMovement()->MaxWalkSpeed = 450;
			break;
		default: break;
		}
	}
}
void APlayerCharacter::Walk(EExecuteBranch Branches)
{
	switch (Branches)
	{
	case EExecuteBranch::Pressed:
		if (LocomotionState != ELocomotionState::Sprint)
		{
			GetCharacterMovement()->MaxWalkSpeed = 150;
		}
		break;
	case EExecuteBranch::Released:
		GetCharacterMovement()->MaxWalkSpeed = 450;
		break;
	default:
		GetCharacterMovement()->MaxWalkSpeed = 450;
		break;
	}
}

void APlayerCharacter::MoveCharacter(float forwardInput, float rightInput)
{
	FRotator directionRotation = FRotator(0, GetControlRotation().Yaw, 0);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(directionRotation), forwardInput);
	AddMovementInput(UKismetMathLibrary::GetRightVector(directionRotation), rightInput);
}
void APlayerCharacter::RotateCharacter(float axisTurn, float axisLook)
{
	if (!hitActor)
	{
		AddControllerYawInput(axisTurn);
		AddControllerPitchInput(axisLook);
	}
}
FVector APlayerCharacter::CalculateDirectionVector()
{
	if (FMath::Abs(GetInputAxisValue("FB")) + FMath::Abs(GetInputAxisValue("LR")) > 0)
	{
		FRotator inputRotation = UKismetMathLibrary::MakeRotFromX(FVector(GetInputAxisValue("FB"), -GetInputAxisValue("LR"), 0));
		return UKismetMathLibrary::Conv_RotatorToVector(FRotator(0, SpringArm->GetTargetRotation().Yaw - inputRotation.Yaw, 0));
	}
	else
	{
		return UKismetMathLibrary::Conv_RotatorToVector(FRotator(0, SpringArm->GetTargetRotation().Yaw, 0));
	}
}

void APlayerCharacter::HardLockTrace()
{
	FVector endPoint = sphereLength * SpringArm->GetTargetRotation().Vector() + GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> Types;
	TArray<AActor*> IgnoreActors;
	Types.Add(EObjectTypeQuery::ObjectTypeQuery3);
	IgnoreActors.Add(this);
	EDrawDebugTrace::Type traceType = EDrawDebugTrace::ForOneFrame;
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), GetActorLocation(), endPoint, sphereRadius, Types, false, IgnoreActors, traceType, LockHitResult, true);
}

void APlayerCharacter::SoftLockTrace()
{
	FVector endPoint = sphereLength * CalculateDirectionVector() + GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> Types;
	TArray<AActor*> IgnoreActors;
	Types.Add(EObjectTypeQuery::ObjectTypeQuery3);
	IgnoreActors.Add(this);
	EDrawDebugTrace::Type traceType = EDrawDebugTrace::ForOneFrame;
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), GetActorLocation(), endPoint, 100, Types, false, IgnoreActors, traceType, LockHitResult, true);
	UKismetSystemLibrary::DrawDebugArrow(GetWorld(), GetActorLocation(), endPoint, 10, FColor::Red, 0, 3);
}

void APlayerCharacter::HardLock()
{
	if (hitActor)
	{
		FRotator targetControlRotation = UKismetMathLibrary::FindLookAtRotation(
			GetActorLocation(), FVector(hitActor->GetActorLocation().X, hitActor->GetActorLocation().Y + 60, hitActor->GetActorLocation().Z));
		FRotator targetActorRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), hitActor->GetActorLocation());
		GetController()->SetControlRotation(UKismetMathLibrary::RInterpTo(GetControlRotation(),targetControlRotation,GetWorld()->GetDeltaSeconds(),interpSpeed));
		SetActorRotation(targetActorRotation,ETeleportType::ResetPhysics);
	}
}

void APlayerCharacter::LockOnTarget()
{
	if (!hitActor)
	{
		HardLockTrace();
		hitActor = Cast<AActor>(LockHitResult.GetActor());
		GetWorldTimerManager().ClearTimer(LockTimerHandle);
		GetWorldTimerManager().SetTimer(LockTimerHandle, this, &APlayerCharacter::HardLock, 0.001, true);
		if(hitActor)
			LockingProps(true);
	}
	else
	{
		hitActor = NULL;
		GetWorldTimerManager().ClearTimer(LockTimerHandle);
		GetWorldTimerManager().SetTimer(LockTimerHandle, this, &APlayerCharacter::SoftLockTrace, 0.001, true);
		LockingProps(false);
		if(hitActor)
			LockingProps(true);
	}
}

void APlayerCharacter::LockingProps(bool bIsPlayerLocked)
{
	bIsPlayerLocked ? GetCharacterMovement()->bOrientRotationToMovement = false : GetCharacterMovement()->bOrientRotationToMovement = true;
	bIsPlayerLocked ? SetFocusState(EFocusState::FocusState) : SetFocusState(EFocusState::FreeState);
}

void APlayerCharacter::ChangeCollision(bool value)
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

void APlayerCharacter::WeaponHitOpponent(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if(Enemy)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, "Enemy got hurt");
		Enemy->GetHitByPlayer();
	}
}

void APlayerCharacter::PlayerAttack(EAttackState playState)
{
	IMontagePlayer* Interface = Cast<IMontagePlayer>(GetMesh()->GetAnimInstance());
	if(Interface && bCanAttack)
	{
		Interface->PlayMontage_Implementation(playState);
	}
}

void APlayerCharacter::GetHitByEnemy_Implementation()
{
}

#pragma region "Getter & Setter"

ELocomotionState APlayerCharacter::GetLocomotionState() { return LocomotionState; }
EActionState APlayerCharacter::GetActionState() { return ActionState; }
EAbilityState APlayerCharacter::GetAbilityState() { return AbilityState; }
EFocusState APlayerCharacter::GetFocusState() { return FocusState; }

void APlayerCharacter::SetLocomotionState(ELocomotionState stateValue) { LocomotionState = stateValue; }
void APlayerCharacter::SetActionState(EActionState stateValue) { ActionState = stateValue; }
void APlayerCharacter::SetAbilityState(EAbilityState stateValue) { AbilityState = stateValue; }
void APlayerCharacter::SetFocusState(EFocusState stateValue) { FocusState = stateValue; }

bool APlayerCharacter::GetCanAttack() { return bCanAttack; }
void APlayerCharacter::SetCanAttack(bool attackValue) { bCanAttack = attackValue; }

/* <---------Locomotion Values---------> */

bool APlayerCharacter::GetIsFalling() { return GetCharacterMovement()->IsFalling(); }
bool APlayerCharacter::GetHasMovementInput() { return (GetCharacterMovement()->GetCurrentAcceleration().Length() / GetCharacterMovement()->MaxAcceleration) > 0.0f; }
bool APlayerCharacter::GetIsMoving() { return GetSpeed() > 1.0f; }
float APlayerCharacter::GetSpeed() { return GetVelocity().Length(); }
FRotator APlayerCharacter::GetAimingRotation() { return GetControlRotation(); }

/* <---------Consturctor Setup---------> */

void APlayerCharacter::SetupSpringArm()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeLocation(FVector(0, 0, 70));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 350;
}
void APlayerCharacter::SetupCamera()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	VisionPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Plane"));
	VisionPlane->SetupAttachment(Camera);
	VisionPlane->SetRelativeLocation(FVector(60,0,0));
	VisionPlane->SetRelativeRotation(FRotator(0,90,-90));
}
void APlayerCharacter::SetupWeapon()
{
	WeaponSlot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponSlot->SetupAttachment(GetMesh(), "hand_rSocket");
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collision"));
	WeaponCollision->SetupAttachment(WeaponSlot);
}
void APlayerCharacter::SetupCharacter()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 450;
	bUseControllerRotationYaw = false;
}

#pragma endregion 


