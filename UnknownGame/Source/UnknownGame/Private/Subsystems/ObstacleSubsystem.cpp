
#include "Subsystems/ObstacleSubsystem.h"


void UObstacleSubsystem::ResetData()
{
	bIsLocked = true;
}


void UObstacleSubsystem::UnlockDoor(){bIsLocked = false;}
bool UObstacleSubsystem::IsDoorLocked() const{return bIsLocked;}