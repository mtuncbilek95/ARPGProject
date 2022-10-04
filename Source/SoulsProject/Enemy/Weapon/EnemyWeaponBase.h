// 2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyWeaponBase.generated.h"

UCLASS()
class SOULSPROJECT_API AEnemyWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AEnemyWeaponBase();

	UPROPERTY(EditDefaultsOnly, Category= "Scene Component")
	USceneComponent* SceneComponent;
	UPROPERTY(EditDefaultsOnly, Category= "Actor Component")
	UStaticMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Actor Component")
	UBoxComponent* WeaponCollision;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable, Category= "Custom Component")
	void ChangeCollision(bool valueCollision);
	UFUNCTION(BlueprintCallable, Category= "Custom Component")
	void CombatOverlapping(AActor* OverlapActor);
};
