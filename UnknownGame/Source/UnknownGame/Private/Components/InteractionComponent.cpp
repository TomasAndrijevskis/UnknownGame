
#include "Components/InteractionComponent.h"
#include "Interfaces/Interactable.h"


void UInteractionComponent::TryInteract()
{
	FHitResult HitResult;
	HitAnything(GetOwner()->GetActorTransform(), HitResult);
	AActor* HitActor = HitResult.GetActor();
	if (IsValid(HitActor) && HitActor->Implements<UInteractable>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Interactable: %s"), *HitActor->GetName());
		IInteractable::Execute_OnInteract(HitActor, GetOwner());
	}
}


void UInteractionComponent::HitAnything(const FTransform& OwnerTransform, FHitResult& OutHit) const
{
	const FVector3d StartLocation = OwnerTransform.GetLocation();
	const FVector3d EndLocation = StartLocation + OwnerTransform.GetRotation().GetForwardVector() * InteractableDistance;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, Channel, Params);
	if (OutHit.bBlockingHit) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 3.f);
}