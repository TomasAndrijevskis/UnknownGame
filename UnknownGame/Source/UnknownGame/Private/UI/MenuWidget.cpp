
#include "UI/MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Start->OnClicked.AddUniqueDynamic(this, &UMenuWidget::StartGame);
}


void UMenuWidget::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}
