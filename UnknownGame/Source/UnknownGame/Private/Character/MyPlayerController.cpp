
#include "Character/MyPlayerController.h"


void AMyPlayerController::ChangePlayerInput(bool bWidgetInput)
{
	SetShowMouseCursor(bWidgetInput);
	if (bWidgetInput)
	{
		FInputModeUIOnly InputMode;
		SetInputMode(InputMode);
	}
	else
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
}