
#include "Objects/Lever.h"
#include "Components/BoxComponent.h"
#include "Subsystems/ObstacleSubsystem.h"


ALever::ALever()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
}


void ALever::OnInteract_Implementation(AActor* InteractingActor)
{
	if (bInteracted) return;
	if (UObstacleSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UObstacleSubsystem>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact with lever"));
		bInteracted = true;
		Subsystem->UnlockDoor();
	}
}

