// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SoulsProject/Character/States/ExecuteBranch.h"
#include "WeaponActor.generated.h"

UCLASS()
class SOULSPROJECT_API AWeaponActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponActor();

	UPROPERTY(EditDefaultsOnly, Category= "Scene Component")
	USceneComponent* SceneComponent;
	UPROPERTY(EditDefaultsOnly, Category= "Actor Component")
	UStaticMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Actor Component")
	UBoxComponent* WeaponCollision;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION(BlueprintCallable, Category= "Custom Component")
	void ChangeCollision(bool value);
	UFUNCTION(BlueprintCallable, Category= "Custom Component")
	void CombatOverlapping(AActor* OverlapActor);
};
