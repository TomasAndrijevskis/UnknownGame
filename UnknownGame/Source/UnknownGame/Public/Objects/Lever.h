
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Lever.generated.h"

class UBoxComponent;
class UStaticMeshComponent;


UCLASS()
class UNKNOWNGAME_API ALever : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	

	ALever();

	virtual void OnInteract_Implementation(AActor* InteractingActor) override;

private:
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Collision;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	bool bInteracted = false;
};
