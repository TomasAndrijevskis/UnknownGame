
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"


class UButton;

UCLASS()
class UNKNOWNGAME_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Start;

	UFUNCTION()
	void StartGame();

	UPROPERTY(EditDefaultsOnly)
	FName LevelName = "ThirdPersonMap";
};
