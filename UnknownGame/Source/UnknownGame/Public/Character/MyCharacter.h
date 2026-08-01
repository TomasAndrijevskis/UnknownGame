
#pragma once

#include "CoreMinimal.h"
#include "Character/UnknownGameCharacter.h"
#include "MyCharacter.generated.h"


class UMainPlayerWidget;
class UPlayersHUD;
class UInteractionComponent;
class UHealthComponent;

UCLASS()
class UNKNOWNGAME_API AMyCharacter : public AUnknownGameCharacter
{
	GENERATED_BODY()

public:

	AMyCharacter();

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TakeDamageAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionInput;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInteractionComponent* InteractionComp;

	void HandleTestDamageInput();

	void BindDelegates();
	
	void PrintHealthChanges(float NewHealth, float MaxHealth, float Delta);

	void OnCollectibleTargetReached();
	
	UFUNCTION()
	void OnDeath();

	void CreatePlayersWidget();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainPlayerWidget> PlayersWidgetClass;
};
