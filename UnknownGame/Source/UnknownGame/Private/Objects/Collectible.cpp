
#include "UnknownGame/Public/Objects/Collectible.h"
#include "Components/SphereComponent.h"
#include "Subsystems/CollectibleSubsystem.h"


ACollectible::ACollectible()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
}


void ACollectible::OnInteract_Implementation(AActor* Interactor)
{
	UE_LOG(LogTemp, Display, TEXT("OnInteract %s"), *this->GetName());
	
	if (UCollectibleSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UCollectibleSubsystem>())
	{
		UE_LOG(LogTemp, Display, TEXT("Collected %s"), *this->GetName());
		Subsystem->ReportCollected();
	}
	Destroy();
}
