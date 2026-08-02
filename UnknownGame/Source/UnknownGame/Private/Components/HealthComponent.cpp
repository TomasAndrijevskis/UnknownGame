
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
	OnHealthChangedDelegate.Broadcast(CurrentHealth, MaxHealth, CurrentHealth - OldHealth);
}


void UHealthComponent::ApplyDamage(const float Amount)
{
	if (bIsDead || Amount <= 0) return;
	UE_LOG(LogTemp, Warning, TEXT("Apply damage %f to %s"), Amount, *GetOwner()->GetName());
	const float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.0f, MaxHealth);
	OnHealthChangedDelegate.Broadcast(CurrentHealth, MaxHealth, CurrentHealth - OldHealth);
	if (CurrentHealth <= 0)
	{
		bIsDead = true;
		UE_LOG(LogTemp, Warning, TEXT("I'm dead %s"), *GetOwner()->GetName())
		OnDeathDelegate.Broadcast();
	}
}


float UHealthComponent::GetMaxHealth() const {return MaxHealth;}
float UHealthComponent::GetCurrentHealth() const {return CurrentHealth;}