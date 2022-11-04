// 2022 Metehan Tuncbilek TR, All rights reserved.


#include "BaseHUD.h"

#include "SoulsProject/Character/Widgets/CharacterMainWidget.h"

ABaseHUD::ABaseHUD()
{
	static ConstructorHelpers::FClassFinder<UCharacterMainWidget> CharacterWidget(TEXT("/Game/PlayerCharacter/UI/MainUIScreen"));
	if (!ensure(CharacterWidget.Class != nullptr)) return;

	UCharacterMainWidget* CharacterMainWidget = CreateWidget<UCharacterMainWidget>(GetWorld(), CharacterWidget.Class);
	if (CharacterMainWidget)
		CharacterMainWidget->AddToViewport(0);
}

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();
}
