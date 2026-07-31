
#include "Components/HealthComponent.h"


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}


void UHealthComponent::Heal(const float Amount)
{
	if (bIsDead || Amount <= 0) return;
	const float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.0f, MaxHealth);
	OnHealthChangedDelegate.Broadcast(CurrentHealth, CurrentHealth - OldHealth);
}


void UHealthComponent::ApplyDamage(const float Amount)
{
	if (bIsDead || Amount <= 0) return;
	const float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.0f, MaxHealth);
	OnHealthChangedDelegate.Broadcast(CurrentHealth, CurrentHealth - OldHealth);
	if (CurrentHealth <= 0)
	{
		bIsDead = true;
		OnDeathDelegate.Broadcast();
	}
}