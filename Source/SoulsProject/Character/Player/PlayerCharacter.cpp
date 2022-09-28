//	2022 Metehan Tuncbilek TR, All rights reserved.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeLocation(FVector(0, 0, 70));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 450;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 450;

	bUseControllerRotationYaw = false;

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), "hand_rSocket");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::Sprint(EExecuteBranch Branches)
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

void APlayerCharacter::Walk(EExecuteBranch Branches)
{
	switch (Branches)
	{
	case EExecuteBranch::Pressed:
		if (LocomotionState != ELocomotionState::Sprint)
		{
			GetCharacterMovement()->MaxWalkSpeed = 170;
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
	UKismetSystemLibrary::DrawDebugArrow(GetWorld(), GetActorLocation(), endPoint, 10, FColor::Red,0,3);
}

void APlayerCharacter::HardLock()
{
	if (hitActor)
	{
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation( GetActorLocation(), FVector(hitActor->GetActorLocation().X,hitActor->GetActorLocation().Y+60,hitActor->GetActorLocation().Z));
		GetController()->SetControlRotation(FRotator(targetRotation.Pitch, targetRotation.Yaw, targetRotation.Roll));
	}
}

void APlayerCharacter::LockOnTarget()
{
	if (!hitActor)
	{
		HardLockTrace();
		hitActor = Cast<AActor>(LockHitResult.GetActor());
		GetWorldTimerManager().ClearTimer(LockTimerHandle);
		GetWorldTimerManager().SetTimer(LockTimerHandle, this, &APlayerCharacter::HardLock, 0.01, true);
	}
	else
	{
		hitActor = NULL;
		GetWorldTimerManager().ClearTimer(LockTimerHandle);
		GetWorldTimerManager().SetTimer(LockTimerHandle, this, &APlayerCharacter::SoftLockTrace, 0.01, true);
	}
}
