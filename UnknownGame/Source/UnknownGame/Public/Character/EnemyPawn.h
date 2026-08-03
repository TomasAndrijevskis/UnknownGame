
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

class UDetectionComponent;
class USphereComponent;
class UAttackComponent;
class UCapsuleComponent;
class UHealthComponent;
class UStaticMeshComponent;

UCLASS()
class UNKNOWNGAME_API AEnemyPawn : public APawn, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:

	AEnemyPawn();

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	
protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	
private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCapsuleComponent> Collision;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> AttackArea;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UHealthComponent> HealthComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttackComponent> AttackComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDetectionComponent> DetectionComp;
	
	void BindDelegates();
	
	void OnDeath();

	UPROPERTY(EditAnywhere, Category = "Gameplay Tags")
	FGameplayTagContainer GameplayTags;
};
