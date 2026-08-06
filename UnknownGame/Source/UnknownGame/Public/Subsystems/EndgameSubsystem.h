
#pragma once

#include "CoreMinimal.h"
#include "Data/EEndgameResults.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EndgameSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCompleted, EEndgameResults);
DECLARE_MULTICAST_DELEGATE(FOnRestarted)
UCLASS()
class UNKNOWNGAME_API UEndgameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void Restart();
	
	FOnCompleted OnCompletedDelegate;
	
};
