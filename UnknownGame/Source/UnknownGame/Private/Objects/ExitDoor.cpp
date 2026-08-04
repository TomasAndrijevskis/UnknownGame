
#include "UnknownGame/Public/Objects/ExitDoor.h"
#include "Components/BoxComponent.h"
#include "Subsystems/CollectibleSubsystem.h"
#include "Subsystems/EndgameSubsystem.h"


AExitDoor::AExitDoor()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;
}


void AExitDoor::OnInteract_Implementation(AActor* Interactor)
{
	if (bIsCompleted) return;
	if (UCollectibleSubsystem* CollectSubsystem = GetGameInstance()->GetSubsystem<UCollectibleSubsystem>())
	{
		if (CollectSubsystem->IsTargetReached())
		{
			if (UEndgameSubsystem* EndgameSubsystem = GetGameInstance()->GetSubsystem<UEndgameSubsystem>())
			{
				UE_LOG(LogTemp, Error, TEXT("Game is finished"));
				bIsCompleted = true;
				EndgameSubsystem->OnCompletedDelegate.Broadcast(EEndgameResults::Win);
			}
		}
	}
}