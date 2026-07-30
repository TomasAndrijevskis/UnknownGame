
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNKNOWNGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable)
	void Heal(const float Amount);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(const float Amount);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable)
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
