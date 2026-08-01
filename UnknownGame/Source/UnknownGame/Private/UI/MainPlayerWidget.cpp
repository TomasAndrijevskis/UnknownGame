
#include "UI/MainPlayerWidget.h"
#include "Components/HealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Subsystems/CollectibleSubsystem.h"


void UMainPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OnCreation();
}


void UMainPlayerWidget::OnCreation()
{
	if (UCollectibleSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UCollectibleSubsystem>())
	{
		UpdateCurrentCollectibles(Subsystem->GetCount(), Subsystem->GetTarget());
		Subsystem->OnCountChangedDelegate.AddUObject(this, &UMainPlayerWidget::UpdateCurrentCollectibles);
	}
	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		if (UHealthComponent* HealthComp = Pawn->FindComponentByClass<UHealthComponent>())
		{
			UpdateHealthBar(HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth(), 0.f);
			HealthComp->OnHealthChangedDelegate.AddUObject(this, &UMainPlayerWidget::UpdateHealthBar);
		}
	}
}


void UMainPlayerWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth, float Delta)
{
	UE_LOG(LogTemp, Display, TEXT("Update health bar %f, %f"), CurrentHealth, MaxHealth);
	ProgressBar_HealthBar->SetPercent(CurrentHealth / MaxHealth);
}


void UMainPlayerWidget::UpdateCurrentCollectibles(int Count, int Target)
{
	UE_LOG(LogTemp, Display, TEXT("Update collectibles %i, %i"), Count, Target);
	TextBlock_CurrentCollectibles->SetText(FText::AsNumber(Count));
	TextBlock_TargetCollectibles->SetText(FText::AsNumber(Target));
}