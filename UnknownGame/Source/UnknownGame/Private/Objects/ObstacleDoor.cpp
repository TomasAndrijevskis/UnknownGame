
#include "Objects/ObstacleDoor.h"
#include "Components/BoxComponent.h"
#include "Subsystems/ObstacleSubsystem.h"


AObstacleDoor::AObstacleDoor()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
}


void AObstacleDoor::OnInteract_Implementation(AActor* InteractingActor)
{
	if (bInteracted) return;
	if (UObstacleSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UObstacleSubsystem>())
	{
		if (Subsystem->IsDoorLocked())
		{
			UE_LOG(LogTemp, Warning, TEXT("Door is locked!"));
			return;
		}
		bInteracted = true;
		UE_LOG(LogTemp, Warning, TEXT("Obstacle door is unlocked"));
	}
}
