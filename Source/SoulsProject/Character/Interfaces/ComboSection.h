//	2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ComboSection.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UComboSection : public UInterface
{
	GENERATED_BODY()
};

class SOULSPROJECT_API IComboSection
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void DefaulAttack() = 0;
	virtual void NextCombo(FName LightAttack, FName HeavyAttack) = 0;
	virtual void SetAttack(bool bCanAttack) = 0;
	
};
