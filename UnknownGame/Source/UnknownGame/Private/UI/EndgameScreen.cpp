
#include "UI/EndgameScreen.h"
#include "Components/TextBlock.h"


void UEndgameScreen::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimation(Anim, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, false);
}


void UEndgameScreen::SetMessage(EEndgameResults Result)
{
	FSlateColor Color;
	switch (Result)
	{
		case EEndgameResults::Win:
		{
			Color = FSlateColor(FColor::Green);
			TextBlock_Message->SetText(FText::FromString("Win"));
			break;
		}
			
		case EEndgameResults::Loss:
		{
			Color = FSlateColor(FColor::Red);
			TextBlock_Message->SetText(FText::FromString("Loss"));
			break;
		}
		default:
		{
			Color = FSlateColor(FColor::White);
			TextBlock_Message->SetText(FText::FromString("Error"));
			break;
		}
	}
	TextBlock_Message->SetColorAndOpacity(Color);
}
