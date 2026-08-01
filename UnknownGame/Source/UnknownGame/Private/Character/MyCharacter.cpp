
#include "Character/MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "Components/AttackComponent.h"
#include "Components/HealthComponent.h"
#include "Components/InteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/CollectibleSubsystem.h"
#include "UI/MainPlayerWidget.h"


AMyCharacter::AMyCharacter()
{
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction component"));
	AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack component"));
}


void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!InteractionComp) return;
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(AttackInput, ETriggerEvent::Started, AttackComp, &UAttackComponent::Attack);
		EnhancedInputComponent->BindAction(InteractionInput, ETriggerEvent::Started, InteractionComp, &UInteractionComponent::TryInteract);
	}
}


void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	BindDelegates();
	CreatePlayersWidget();
}


void AMyCharacter::BindDelegates()
{
	if (!HealthComp) return;
	HealthComp->OnHealthChangedDelegate.AddUObject(this, &AMyCharacter::PrintHealthChanges);
	HealthComp->OnDeathDelegate.AddUObject(this, &AMyCharacter::OnDeath);
	UCollectibleSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UCollectibleSubsystem>();
	if (!Subsystem) return;
	Subsystem->OnTargetReachedDelegate.AddUObject(this, &AMyCharacter::OnCollectibleTargetReached);
}


void AMyCharacter::OnCollectibleTargetReached()
{
	UE_LOG(LogTemp, Error, TEXT("%s | Target reached"), *this->GetName());
}


void AMyCharacter::PrintHealthChanges(float NewHealth, float MaxHealth, float Delta)
{
	UE_LOG(LogTemp, Warning, TEXT("Health: %f, Delta: %f"), NewHealth, Delta);
}


void AMyCharacter::OnDeath()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;
	this->DisableInput(PC);
}


void AMyCharacter::CreatePlayersWidget()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PlayersWidgetClass || !PC) return;
	TObjectPtr<UMainPlayerWidget> PlayersWidgetRef = CreateWidget<UMainPlayerWidget>(PC, PlayersWidgetClass);
	if (!PlayersWidgetRef) return;
	PlayersWidgetRef->AddToViewport(0);
}


void AMyCharacter::HandleTestDamageInput()
{
	HealthComp->ApplyDamage(10);
}
