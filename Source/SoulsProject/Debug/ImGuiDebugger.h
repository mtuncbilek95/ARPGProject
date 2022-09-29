// 2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <imgui.h>
#include "ImGuiDebugger.generated.h"

UCLASS()
class SOULSPROJECT_API AImGuiDebugger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AImGuiDebugger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


};
