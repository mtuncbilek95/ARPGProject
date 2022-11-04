// 2022 Metehan Tuncbilek TR, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponCollision.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UWeaponCollision : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOULSPROJECT_API IWeaponCollision
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void TraceWeaponHit() = 0;
	virtual void TopLine() = 0;
	virtual void BottomLine() = 0;
	virtual void EndWeaponCollision() = 0;
};
