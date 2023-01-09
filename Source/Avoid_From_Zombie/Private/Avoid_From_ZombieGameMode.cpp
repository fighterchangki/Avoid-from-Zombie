// Copyright Epic Games, Inc. All Rights Reserved.

#include "Avoid_From_ZombieGameMode.h"
#include "Avoid_From_ZombieCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Avoid_From_Zombie.h"
AAvoid_From_ZombieGameMode::AAvoid_From_ZombieGameMode()
{
	// set default pawn class to our Blueprinted character
	
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PRINT_CALLINFO();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CALLINFO);
	PRINT_LOG(TEXT("My Log : %s"), TEXT("TPS project!!"));
	
}
