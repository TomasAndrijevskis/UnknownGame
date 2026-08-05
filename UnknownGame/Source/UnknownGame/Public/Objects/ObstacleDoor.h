
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "ObstacleDoor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class UNKNOWNGAME_API AObstacleDoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	
	AObstacleDoor();

	virtual void OnInteract_Implementation(AActor* InteractingActor) override;

private:

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Collision;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	bool bInteracted = false;
};
