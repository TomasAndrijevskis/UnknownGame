
#include "UnknownGame/Public/GameMode/UnknownGameGameMode.h"
#include "UnknownGame/Public/Character/UnknownGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnknownGameGameMode::AUnknownGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
