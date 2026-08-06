
#include "Character/MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "Character/MyPlayerController.h"
#include "Components/AttackComponent.h"
#include "Components/DamageFeedbackComponent.h"
#include "Components/HealthComponent.h"
#include "Components/InteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/CollectibleSubsystem.h"
#include "Subsystems/EndgameSubsystem.h"
#include "UI/EndgameScreen.h"
#include "UI/MainPlayerWidget.h"


AMyCharacter::AMyCharacter()
{
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction component"));
	AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack component"));
	DamageFeedbackComp = CreateDefaultSubobject<UDamageFeedbackComponent>(TEXT("Damage feedback component"));
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
	if (HealthComp)
	{
		HealthComp->OnDeathDelegate.AddUObject(this, &AMyCharacter::OnDeath);
		if (DamageFeedbackComp) HealthComp->OnHealthChangedDelegate.AddUObject(DamageFeedbackComp, &UDamageFeedbackComponent::OnDamageReceived);
	}
	if (UCollectibleSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UCollectibleSubsystem>())
	{
		Subsystem->OnTargetReachedDelegate.AddUObject(this, &AMyCharacter::OnCollectibleTargetReached);
	}
	if (UEndgameSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UEndgameSubsystem>())
	{
		Subsystem->OnCompletedDelegate.AddUObject(this, &AMyCharacter::OnGameEnd);
	}
}


void AMyCharacter::OnDeath()
{
	OnGameEnd(EEndgameResults::Loss);
}


void AMyCharacter::OnGameEnd(EEndgameResults Result)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;
	this->DisableInput(PC);
	CreateEndgameWidget(Result);
}


void AMyCharacter::CreateEndgameWidget(EEndgameResults Result)
{
	AMyPlayerController* PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!EndgameWidgetClass || !PC) return;
	TObjectPtr<UEndgameScreen> EndgameWidgetRef = CreateWidget<UEndgameScreen>(PC, EndgameWidgetClass);
	if (!EndgameWidgetRef) return;
	EndgameWidgetRef->SetMessage(Result);
	EndgameWidgetRef->AddToViewport(0);
	PC->ChangePlayerInput(true);
}


void AMyCharacter::CreatePlayersWidget()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PlayersWidgetClass || !PC) return;
	TObjectPtr<UMainPlayerWidget> PlayersWidgetRef = CreateWidget<UMainPlayerWidget>(PC, PlayersWidgetClass);
	if (!PlayersWidgetRef) return;
	PlayersWidgetRef->AddToViewport(0);
}


void AMyCharacter::OnCollectibleTargetReached()
{
	UE_LOG(LogTemp, Error, TEXT("%s | Target reached"), *this->GetName());
}

void AMyCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const{TagContainer = GameplayTags;}
bool AMyCharacter::HasMatchingGameplayTag(FGameplayTag TagToCheck) const{return GameplayTags.HasTag(TagToCheck);}