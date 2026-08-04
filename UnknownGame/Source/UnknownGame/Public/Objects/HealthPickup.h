
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "HealthPickup.generated.h"

UCLASS()
class UNKNOWNGAME_API AHealthPickup : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	

	virtual void OnInteract_Implementation(AActor* Interactor) override;
	
private:

	UPROPERTY(EditDefaultsOnly)
	float HealAmount = 15.f;
};
