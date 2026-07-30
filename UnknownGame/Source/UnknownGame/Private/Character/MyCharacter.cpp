
#include "Character/MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"


AMyCharacter::AMyCharacter()
{
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
}


void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(HealAction, ETriggerEvent::Started, this, &AMyCharacter::Heal);
		EnhancedInputComponent->BindAction(TakeDamageAction, ETriggerEvent::Started, this, &AMyCharacter::TakeDamage);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	BindDelegates();
}


void AMyCharacter::BindDelegates()
{
	if (!HealthComp) return;
	HealthComp->OnHealthChangedDelegate.AddUniqueDynamic(this, &AMyCharacter::PrintHealthChanges);
	HealthComp->OnDeathDelegate.AddUniqueDynamic(this, &AMyCharacter::OnDeath);
}


void AMyCharacter::PrintHealthChanges(float NewHealth, float Delta)
{
	UE_LOG(LogTemp, Warning, TEXT("Health: %f, Delta: %f"), NewHealth, Delta);
}


void AMyCharacter::OnDeath()
{
	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PC) return;
	this->DisableInput(PC);
}


void AMyCharacter::Heal()
{
	HealthComp->Heal(10);
}


void AMyCharacter::TakeDamage()
{
	HealthComp->TakeDamage(10);
}
