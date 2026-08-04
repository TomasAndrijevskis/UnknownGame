
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageFeedbackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNKNOWNGAME_API UDamageFeedbackComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	void OnDamageReceived(float CurrentHealth, float MaxHealth, float Delta);
	
private:

	UPROPERTY(EditDefaultsOnly)
	float StrengthMultiplier = 1000.f;
};
