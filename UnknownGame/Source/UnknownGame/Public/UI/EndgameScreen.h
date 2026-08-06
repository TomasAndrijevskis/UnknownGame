
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/EEndgameResults.h"
#include "EndgameScreen.generated.h"


class UButton;
class UTextBlock;

UCLASS()
class UNKNOWNGAME_API UEndgameScreen : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetMessage(EEndgameResults Result);

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Message;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Anim;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Restart;

	UFUNCTION()
	void OnButtonClicked();
};