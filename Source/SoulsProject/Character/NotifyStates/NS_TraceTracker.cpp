// 2022 Metehan Tuncbilek TR, All rights reserved.

#include "NS_TraceTracker.h"

#include "SoulsProject/Character/Player/PlayerCharacter.h"

void UNS_TraceTracker::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	IWeaponCollision* Interface = Cast<IWeaponCollision>(MeshComp->GetOwner());
	if(Interface)
		Interface->TraceWeaponHit(true);
}

void UNS_TraceTracker::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	IWeaponCollision* Interface = Cast<IWeaponCollision>(MeshComp->GetOwner());
	if(Interface)
		Interface->TraceWeaponHit(false);
		
}

void UNS_TraceTracker::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}
