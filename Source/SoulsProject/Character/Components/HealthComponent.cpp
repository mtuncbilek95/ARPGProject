// 2022 Metehan Tuncbilek TR, All rights reserved.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	currentHealthAmount = maximumHealthAmount;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::ComponentTakeDamge);
}

void UHealthComponent::ComponentTakeDamge(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage > 0.0f)
	{
		currentHealthAmount -= Damage;
		OnDamageTakenDelegate.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Enemy Health: %f"), currentHealthAmount);
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UHealthComponent::GetHealth() { return currentHealthAmount; }
