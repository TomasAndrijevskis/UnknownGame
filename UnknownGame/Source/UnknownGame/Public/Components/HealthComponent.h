
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, float, float);
DECLARE_MULTICAST_DELEGATE(FOnDeath);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNKNOWNGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable)
	void Heal(const float Amount);

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(const float Amount);

	float GetMaxHealth() const;

	float GetCurrentHealth() const;
	
	FOnHealthChanged OnHealthChangedDelegate;
	
	FOnDeath OnDeathDelegate;
	
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	float CurrentHealth = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;

	bool bIsDead = false;
};
