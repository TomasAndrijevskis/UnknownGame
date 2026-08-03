
#include "Actors/ExitDoor.h"
#include "Components/BoxComponent.h"
#include "Subsystems/CollectibleSubsystem.h"


AExitDoor::AExitDoor()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;
}


void AExitDoor::OnInteract_Implementation(AActor* Interactor)
{
	if (bIsCompleted) return;
	if (UCollectibleSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UCollectibleSubsystem>())
	{
		if (Subsystem->IsTargetReached())
		{
			UE_LOG(LogTemp, Error, TEXT("Game is finished"));
			bIsCompleted = true;
			Subsystem->OnCompletedDelegate.Broadcast(EEndgameResults::Win);
		}
	}
}