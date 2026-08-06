
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "Character/UnknownGameCharacter.h"
#include "Data/EEndgameResults.h"
#include "MyCharacter.generated.h"


class AMyPlayerController;
class UDamageFeedbackComponent;
class UEndgameScreen;
class UAttackComponent;
class UMainPlayerWidget;
class UPlayersHUD;
class UInteractionComponent;
class UHealthComponent;

UCLASS()
class UNKNOWNGAME_API AMyCharacter : public AUnknownGameCharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:

	AMyCharacter();

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	
protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionInput;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInteractionComponent* InteractionComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAttackComponent* AttackComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDamageFeedbackComponent> DamageFeedbackComp;
	
	void BindDelegates();
	
	void OnCollectibleTargetReached();
	
	void OnGameEnd(EEndgameResults Result);

	void OnDeath();
	
	void CreatePlayersWidget();

	void CreateEndgameWidget(EEndgameResults Result);
	
	UPROPERTY(EditAnywhere, Category = "Gameplay Tags")
	FGameplayTagContainer GameplayTags;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainPlayerWidget> PlayersWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEndgameScreen> EndgameWidgetClass;

	UPROPERTY()
	AMyPlayerController* PC;
};
