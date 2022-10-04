//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerWeaponBase.generated.h"

UCLASS()
class SOULSPROJECT_API APlayerWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	APlayerWeaponBase();

	UPROPERTY(EditDefaultsOnly, Category= "Scene Component")
	USceneComponent* SceneComponent;
	UPROPERTY(EditDefaultsOnly, Category= "Actor Component")
	UStaticMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Actor Component")
	UBoxComponent* WeaponCollision;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION(BlueprintCallable, Category= "Custom Component")
	void ChangeCollision(bool value);
	UFUNCTION(BlueprintCallable, Category= "Custom Component")
	void CombatOverlapping(AActor* OverlapActor);
};
