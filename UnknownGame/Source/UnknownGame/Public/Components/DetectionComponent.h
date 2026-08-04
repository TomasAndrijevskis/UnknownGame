
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DetectionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNKNOWNGAME_API UDetectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void InitComponent(UPrimitiveComponent* Area);

	bool IsAnyoneInRange() const;

	FRotator GetLookAtRotation() const;

	FVector3d GetEnemyLocation() const;
	
private:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY()
	TArray<AActor*> Actors;

	FRotator DefaultRotation;

	float AttackDistance;
};
