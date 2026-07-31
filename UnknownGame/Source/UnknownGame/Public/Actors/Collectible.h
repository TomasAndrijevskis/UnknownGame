
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Collectible.generated.h"

class USphereComponent;

UCLASS()
class UNKNOWNGAME_API ACollectible : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	

	ACollectible();

	virtual void OnInteract_Implementation(AActor* Interactor) override;
	
private:

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
};
