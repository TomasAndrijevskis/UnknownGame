
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "ExitDoor.generated.h"

class UBoxComponent;

UCLASS()
class UNKNOWNGAME_API AExitDoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	

	AExitDoor();
	
	virtual void OnInteract_Implementation(AActor* Interactor) override;
	
private:

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* Collision;
	
	bool bIsCompleted = false;
};