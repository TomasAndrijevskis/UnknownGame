
#include "UnknownGame/Public/Objects/HealthPickup.h"
#include "Components/HealthComponent.h"


void AHealthPickup::OnInteract_Implementation(AActor* Interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("OnInteract_Implementation"));
	if (UHealthComponent* HealthComp = Interactor ? Interactor->FindComponentByClass<UHealthComponent>() : nullptr)
	{
		HealthComp->Heal(HealAmount);
		Destroy();
	}
}
