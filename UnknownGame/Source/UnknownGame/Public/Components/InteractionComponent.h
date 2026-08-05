
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNKNOWNGAME_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void TryInteract();

private:

	void HitAnything(const FTransform& OwnerTransform, FHitResult& OutHit) const;

	UPROPERTY(EditDefaultsOnly)
	float InteractableDistance = 200.f;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> Channel;
};
