// 2022 Metehan Tuncbilek TR, All rights reserved.


#include "NS_WeaponCollision.h"

#include "SoulsProject/Character/Interfaces/WeaponCollision.h"

void UNS_WeaponCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	IWeaponCollision* Interface = Cast<IWeaponCollision>(MeshComp->GetOwner());
	if(Interface)
	{
		Interface->ChangeCollision(true);
		UE_LOG(LogTemp, Warning, TEXT("Open"));
	}
}

void UNS_WeaponCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	IWeaponCollision* Interface = Cast<IWeaponCollision>(MeshComp->GetOwner());
	if(Interface)
	{
		Interface->ChangeCollision(false);
		UE_LOG(LogTemp, Warning, TEXT("Close"));
	}
}
