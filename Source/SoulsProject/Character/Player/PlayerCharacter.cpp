//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "PlayerCharacter.h"

#include "SWarningOrErrorBox.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SoulsProject/Character/Effects/AttackCameraShake.h"
#include "SoulsProject/Character/Interfaces/MontagePlayer.h"
#include "SoulsProject/Enemy/Base/EnemyBase.h"

#pragma region "Constructor"

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupSpringArm();
	SetupCamera();
	SetupCharacter();
	SetupWeapon();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDamageTakenDelegate.AddDynamic(this, &APlayerCharacter::Execute_TakeDamage);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;
}

#pragma endregion

#pragma region "Initial Input Functions"

void APlayerCharacter::Sprint(EExecuteBranch Branches)
{
	if (FocusState == EFocusState::FreeState)
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
		AddControllerPitchInput(axisLook);
		AddControllerYawInput(axisTurn);
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

#pragma endregion

#pragma region "Target Locking System"

void APlayerCharacter::HardLockTrace()
{
	FVector endPoint = sphereLength * SpringArm->GetTargetRotation().Vector() + GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> Types;
	TArray<AActor*> IgnoreActors;
	Types.Add(EObjectTypeQuery::ObjectTypeQuery3);
	IgnoreActors.Add(this);
	EDrawDebugTrace::Type traceType = EDrawDebugTrace::ForOneFrame;
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), GetActorLocation(), endPoint, sphereRadius, Types, false, IgnoreActors, traceType,
	                                                  LockHitResult, true);
}

void APlayerCharacter::SoftLockTrace()
{
	FVector endPoint = sphereLength * CalculateDirectionVector() + GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> Types;
	TArray<AActor*> IgnoreActors;
	Types.Add(EObjectTypeQuery::ObjectTypeQuery3);
	IgnoreActors.Add(this);
	EDrawDebugTrace::Type traceType = EDrawDebugTrace::ForOneFrame;
	UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), GetActorLocation(), endPoint, 100, Types, false, IgnoreActors, traceType,
	                                                  LockHitResult,
	                                                  true);
	UKismetSystemLibrary::DrawDebugArrow(GetWorld(), GetActorLocation(), endPoint, 10, FColor::Red, 0, 3);
}

void APlayerCharacter::HardLock()
{
	if (hitActor)
	{
		FRotator targetControlRotation = UKismetMathLibrary::FindLookAtRotation(
			GetActorLocation(), FVector(hitActor->GetActorLocation().X, hitActor->GetActorLocation().Y + 60, hitActor->GetActorLocation().Z));
		FRotator targetActorRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), hitActor->GetActorLocation());
		GetController()->SetControlRotation(UKismetMathLibrary::RInterpTo(GetControlRotation(), targetControlRotation, GetWorld()->GetDeltaSeconds(),
		                                                                  interpSpeed));
		SetActorRotation(targetActorRotation, ETeleportType::ResetPhysics);
	}
}

void APlayerCharacter::LockOnTarget()
{
	if (!hitActor && LockHitResult.GetActor())
	{
		HardLockTrace();
		hitActor = Cast<AActor>(LockHitResult.GetActor());
		GetWorldTimerManager().ClearTimer(LockTimerHandle);
		GetWorldTimerManager().SetTimer(LockTimerHandle, this, &APlayerCharacter::HardLock, 0.001, true);
		hitActor ? LockingProps(true) : LockingProps(false);
	}
	else if (!hitActor && !LockHitResult.GetActor())
	{
		hitActor = NULL;
		GetWorldTimerManager().ClearTimer(LockTimerHandle);
		GetWorldTimerManager().SetTimer(LockTimerHandle, this, &APlayerCharacter::SoftLockTrace, 0.001, true);
		hitActor ? LockingProps(true) : LockingProps(false);
	}
	else
	{
		hitActor = NULL;
		GetWorldTimerManager().ClearTimer(LockTimerHandle);
		GetWorldTimerManager().SetTimer(LockTimerHandle, this, &APlayerCharacter::SoftLockTrace, 0.001, true);
		hitActor ? LockingProps(true) : LockingProps(false);
	}
}

void APlayerCharacter::LockingProps(bool bIsPlayerLocked)
{
	bIsPlayerLocked ? GetCharacterMovement()->bOrientRotationToMovement = false : GetCharacterMovement()->bOrientRotationToMovement = true;
	bIsPlayerLocked ? SetFocusState(EFocusState::FocusState) : SetFocusState(EFocusState::FreeState);
}

#pragma endregion

#pragma region "Combat Detection"

void APlayerCharacter::WeaponHitOpponent(const FHitResult HitResult)
{
	TSubclassOf<UDamageType> dmgType;
	AEnemyBase* Enemy = Cast<AEnemyBase>(HitResult.GetActor());
	if (Enemy && !bWeaponOverlapped)
	{
		UGameplayStatics::ApplyDamage(Enemy, FMath::RandRange(10, 15), GetController(), this, dmgType);
		TSubclassOf<UAttackCameraShake> Shake = UAttackCameraShake::StaticClass();
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(Shake);
		bWeaponOverlapped = true;
	}
}

void APlayerCharacter::PlayerAttack(EAttackState playState)
{
	IMontagePlayer* Interface = Cast<IMontagePlayer>(GetMesh()->GetAnimInstance());
	if (Interface && bCanAttack)
	{
		Interface->PlayMontage_Implementation(playState);
	}
}

void APlayerCharacter::TraceWeaponHit()
{
	BottomLine();
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), FirstBot, NextTop, ETraceTypeQuery::TraceTypeQuery2, false, ActorsToIgnore,
	                                      EDrawDebugTrace::None, HitResult, true);
	WeaponHitOpponent(HitResult);
	TopLine();
}

void APlayerCharacter::TopLine()
{
	NextTop = WeaponSlot->GetSocketLocation("Weapon_Top");
}

void APlayerCharacter::BottomLine()
{
	FirstBot = WeaponSlot->GetSocketLocation("Weapon_Bot");
}

void APlayerCharacter::EndWeaponCollision()
{
	bWeaponOverlapped = false;
}

#pragma endregion

#pragma region "Get Damage Functions"

void APlayerCharacter::Execute_TakeDamage()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,
	                                 ("Player Health: " + UKismetStringLibrary::Conv_IntToString(HealthComponent->GetHealth())));
}

void APlayerCharacter::GetHitByEnemy_Implementation()
{
}

#pragma endregion

#pragma region "Getter & Setter"

ELocomotionState APlayerCharacter::GetLocomotionState() { return LocomotionState; }
EActionState APlayerCharacter::GetActionState() { return ActionState; }
EAbilityState APlayerCharacter::GetAbilityState() { return AbilityState; }
EFocusState APlayerCharacter::GetFocusState() { return FocusState; }

void APlayerCharacter::SetLocomotionState(ELocomotionState stateValue) { LocomotionState = stateValue; }
void APlayerCharacter::SetActionState(EActionState stateValue) { ActionState = stateValue; }
void APlayerCharacter::SetAbilityState(EAbilityState stateValue) { AbilityState = stateValue; }
void APlayerCharacter::SetFocusState(EFocusState stateValue) { FocusState = stateValue; }
void APlayerCharacter::SetCanAttack(bool attackValue) { bCanAttack = attackValue; }

bool APlayerCharacter::GetCanAttack() { return bCanAttack; }

/* <---------Locomotion Values---------> */

bool APlayerCharacter::GetIsFalling() { return GetCharacterMovement()->IsFalling(); }

bool APlayerCharacter::GetHasMovementInput()
{
	return (GetCharacterMovement()->GetCurrentAcceleration().Length() / GetCharacterMovement()->MaxAcceleration) > 0.0f;
}

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
	VisionPlane->SetRelativeLocation(FVector(60, 0, 0));
	VisionPlane->SetRelativeRotation(FRotator(0, 90, -90));
}

void APlayerCharacter::SetupWeapon()
{
	WeaponSlot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponSlot->SetupAttachment(GetMesh(), "hand_rSocket");
}

void APlayerCharacter::SetupCharacter()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->RegisterComponent();

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 450;
	bUseControllerRotationYaw = false;
}

#pragma endregion
