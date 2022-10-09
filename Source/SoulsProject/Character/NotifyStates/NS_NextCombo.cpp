// 2022 Metehan Tuncbilek TR, All rights reserved.


#include "NS_NextCombo.h"

#include "Kismet/KismetSystemLibrary.h"
#include "SoulsProject/Character/Interfaces/ComboSection.h"

void UNS_NextCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	IComboSection* Interface = Cast<IComboSection>(MeshComp->GetAnimInstance());
	if (Interface)
	{
		Interface->NextCombo(LightName, HeavyName);
		Interface->SetAttack(true);
	}
}

void UNS_NextCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	IComboSection* Interface = Cast<IComboSection>(MeshComp->GetAnimInstance());
	if (Interface)
	{
		Interface->DefaulAttack();
		Interface->SetAttack(false);
	}
}
