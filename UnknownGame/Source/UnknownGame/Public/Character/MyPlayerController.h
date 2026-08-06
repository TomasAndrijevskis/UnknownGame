
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


UCLASS()
class UNKNOWNGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void ChangePlayerInput(bool bWidgetInput);
};
