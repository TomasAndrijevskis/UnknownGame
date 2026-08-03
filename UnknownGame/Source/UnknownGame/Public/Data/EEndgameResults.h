
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EEndgameResults: uint8
{
	Win UMETA(DisplayName = "Win"),
	Loss UMETA(DisplayName = "Loss"),
};