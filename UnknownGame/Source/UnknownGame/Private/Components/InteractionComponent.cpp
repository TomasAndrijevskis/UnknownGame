
#include "Components/InteractionComponent.h"
#include "Interfaces/Interactable.h"


void UInteractionComponent::TryInteract() const
{
	FHitResult HitResult;
	HitAnything(GetOwner()->GetActorTransform(), HitResult);
	AActor* HitActor = HitResult.GetActor();
	if (HitActor && HitActor->Implements<UInteractable>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Interactable"));
		IInteractable::Execute_OnInteract(GetOwner(), HitActor);
	}
}


void UInteractionComponent::HitAnything(const FTransform& OwnerTransform, FHitResult& OutHit) const
{
	const FVector3d StartLocation = OwnerTransform.GetLocation();
	const FVector3d EndLocation = StartLocation + OwnerTransform.GetRotation().GetForwardVector() * InteractableDistance;
	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility);
	if (OutHit.bBlockingHit) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 3.f);
}