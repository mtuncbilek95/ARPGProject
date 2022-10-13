// 2022 Metehan Tuncbilek TR, All rights reserved.

#include "NS_TraceTracker.h"

#include "SoulsProject/Character/Player/PlayerCharacter.h"

void UNS_TraceTracker::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	APlayerCharacter* Ref = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if(Ref)
		Ref->bCanActiveTrace = true;
}

void UNS_TraceTracker::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	APlayerCharacter* Ref = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if(Ref)
		Ref->bCanActiveTrace = false;
}
