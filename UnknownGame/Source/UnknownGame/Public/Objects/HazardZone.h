
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HazardZone.generated.h"

class USphereComponent;

UCLASS()
class UNKNOWNGAME_API AHazardZone : public AActor
{
	GENERATED_BODY()
	
public:	

	AHazardZone();


protected:

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Collision;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(EditAnywhere)
	float Damage = 12.f;

	UPROPERTY(EditAnywhere)
	float DamageInterval = .5f;
	
	TMap<TObjectPtr<AActor>, FTimerHandle> ActiveTimers;
};
