// Copyright Epic Games, Inc. All Rights Reserved.

#include "T3GameMode.h"
#include "T3Character.h"
#include "UObject/ConstructorHelpers.h"

AT3GameMode::AT3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
