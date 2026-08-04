
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UDamageFeedbackComponent;
class AEnemyAIController;
class UDetectionComponent;
class USphereComponent;
class UAttackComponent;
class UCapsuleComponent;
class UHealthComponent;
class UStaticMeshComponent;
UCLASS()
class UNKNOWNGAME_API AEnemyCharacter : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()


public:

	AEnemyCharacter();

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	
protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
private:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> AttackArea;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> ChaseArea;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UHealthComponent> HealthComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttackComponent> AttackComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDamageFeedbackComponent> DamageFeedbackComp;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDetectionComponent> DetectAttackComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDetectionComponent> DetectMovementComp;
	
	void BindDelegates();
	
	void OnDeath();
	
	UPROPERTY()
	AEnemyAIController* AIController;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay Tags")
	FGameplayTagContainer GameplayTags;

	float AcceptanceDistance;
};