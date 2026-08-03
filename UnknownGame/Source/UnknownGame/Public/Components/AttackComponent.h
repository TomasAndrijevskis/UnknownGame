
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNKNOWNGAME_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void Attack();

	float GetAttackDistance() const;
	
private:

	void HitAnything(const FTransform& OwnerTransform, FHitResult& OutHit) const;

	void StartCooldown();

	void OnCooldownEnded();
	
	UPROPERTY(EditDefaultsOnly)
	float Cooldown = 1.f;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 5.f;

	UPROPERTY(EditDefaultsOnly)
	float AttackDistance = 100.f;

	bool bIsOnCooldown = false;
	
	FTimerHandle TimerHandle;
};
