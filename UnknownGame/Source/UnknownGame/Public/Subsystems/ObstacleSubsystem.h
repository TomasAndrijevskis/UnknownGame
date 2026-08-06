
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ObstacleSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnLeverInteracted);
UCLASS()
class UNKNOWNGAME_API UObstacleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	bool IsDoorLocked() const;

	void UnlockDoor();

	void ResetData();
	
private:

	bool bIsLocked = true;
};
