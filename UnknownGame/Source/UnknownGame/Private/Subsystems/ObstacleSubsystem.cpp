
#include "Subsystems/ObstacleSubsystem.h"

bool UObstacleSubsystem::IsDoorLocked() const
{
	return bIsLocked;
}


void UObstacleSubsystem::UnlockDoor()
{
	bIsLocked = false;
}
