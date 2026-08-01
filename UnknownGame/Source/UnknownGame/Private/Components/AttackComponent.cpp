
#include "Components/AttackComponent.h"
#include "Components/HealthComponent.h"


void UAttackComponent::Attack()
{
	if (!GetOwner() || bIsOnCooldown) return;
	FTransform OwnerTransform = GetOwner()->GetActorTransform();
	FHitResult OutHit;
	HitAnything(OwnerTransform, OutHit);
	if (AActor* HitActor = OutHit.GetActor())
	{
		if (UHealthComponent* HealthComp = HitActor->FindComponentByClass<UHealthComponent>())
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack"));
			HealthComp->ApplyDamage(Damage);
		}
	}
	StartCooldown();
}


void UAttackComponent::HitAnything(const FTransform& OwnerTransform, FHitResult& OutHit) const
{
	FVector3d StartLocation = OwnerTransform.GetLocation();
	FVector3d EndLocation = StartLocation + OwnerTransform.GetRotation().GetForwardVector() * AttackDistance;
	GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility);
	if (OutHit.bBlockingHit) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 3.f);
}


void UAttackComponent::StartCooldown()
{
	bIsOnCooldown = true;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAttackComponent::OnCooldownEnded, Cooldown, false);
}


void UAttackComponent::OnCooldownEnded()
{
	bIsOnCooldown = false;
}
