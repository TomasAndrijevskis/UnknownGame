
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainPlayerWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class UNKNOWNGAME_API UMainPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar_HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_CurrentCollectibles;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_TargetCollectibles;
	
	void UpdateHealthBar(float CurrentHealth, float MaxHealth, float Delta);

	void UpdateCurrentCollectibles(int Count, int Target);

	void OnCreation();
};
