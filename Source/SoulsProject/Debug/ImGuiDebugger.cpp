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
	APlayerCharacter* CharRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ImGui::Begin("Character Debugger", false, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::InputFloat("Sphere Radius: ", &sphereRad, 10, 100);
	ImGui::InputFloat("Sphere Length: ", &sphereLength, 100, 500);
	ImGui::InputFloat("Camera Focus Speed: ", &interpSpeed, 0.5, 1);
	
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();

	if(sphereRad != sphereRadOld && CharRef || sphereLength != sphereLengthOld || interpSpeed != interpSpeedOld )
	{
		sphereRadOld = sphereRad;
		sphereLengthOld = sphereLength;
		interpSpeedOld = interpSpeed;
		CharRef->SetSphereRad(sphereRad);
		CharRef->SetSphereLength(sphereLength);
		CharRef->SetInterpSpeed(interpSpeed);
	}
}

