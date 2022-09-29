// 2022 Metehan Tuncbilek TR, All rights reserved.


#include "ImGuiDebugger.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SoulsProject/Character/Player/PlayerCharacter.h"


// Sets default values
AImGuiDebugger::AImGuiDebugger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AImGuiDebugger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AImGuiDebugger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

