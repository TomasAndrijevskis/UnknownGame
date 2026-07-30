
#pragma once

#include "CoreMinimal.h"
#include "Character/UnknownGameCharacter.h"
#include "MyCharacter.generated.h"


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
	UInputAction* HealAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TakeDamageAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComp;

	void Heal();

	void TakeDamage();

	void BindDelegates();

	UFUNCTION()
	void PrintHealthChanges(float NewHealth, float Delta);

	UFUNCTION()
	void OnDeath();
};
