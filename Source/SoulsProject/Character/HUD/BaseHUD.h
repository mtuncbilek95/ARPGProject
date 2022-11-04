// 2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SoulsProject/Character/Widgets/CharacterMainWidget.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class SOULSPROJECT_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
	ABaseHUD();

	virtual void DrawHUD() override;
	
};
