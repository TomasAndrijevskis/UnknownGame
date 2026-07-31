
#include "Character/MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/HealthComponent.h"
#include "Components/InteractionComponent.h"
#include "Kismet/GameplayStatics.h"


AMyCharacter::AMyCharacter()
{
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction component"));
}


void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!InteractionComp) return;
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(TakeDamageAction, ETriggerEvent::Started, this, &AMyCharacter::HandleTestDamageInput);
		EnhancedInputComponent->BindAction(InteractionInput, ETriggerEvent::Started, InteractionComp, &UInteractionComponent::TryInteract);
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
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;
	this->DisableInput(PC);
}


void AMyCharacter::HandleTestDamageInput()
{
	HealthComp->ApplyDamage(10);
}
