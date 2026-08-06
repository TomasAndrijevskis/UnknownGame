
#include "Subsystems/EndgameSubsystem.h"
#include "Character/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/CollectibleSubsystem.h"
#include "Subsystems/ObstacleSubsystem.h"


void UEndgameSubsystem::Restart()
{
	if (ULevel* CurrentLevel = GetWorld()->GetCurrentLevel())
	{
		if (UCollectibleSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UCollectibleSubsystem>())
		{
			Subsystem->ResetData();
		}
		if (UObstacleSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UObstacleSubsystem>())
		{
			Subsystem->ResetData();
		}
		/*if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			PC->ChangePlayerInput(false);
		}*/
		UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevel->GetName()), true);
	}
}
