
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

class UAttackComponent;
class UCapsuleComponent;
class UHealthComponent;
class UStaticMeshComponent;

UCLASS()
class UNKNOWNGAME_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:

	AEnemyPawn();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> Collision;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UHealthComponent> HealthComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttackComponent> AttackComp;
	
	void BindDelegates();
	
	void OnDeath();
	
};
