
#include "Character/Enemy/EnemyCharacter.h"

#include "Components/SphereComponent.h"
#include "Components/AttackComponent.h"
#include "Components/DetectionComponent.h"
#include "Components/HealthComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackArea = CreateDefaultSubobject<USphereComponent>(TEXT("Attack area"));
	AttackArea->SetupAttachment(GetRootComponent());

	ChaseArea = CreateDefaultSubobject<USphereComponent>(TEXT("Chase area"));
	ChaseArea->SetupAttachment(GetRootComponent());

	
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack component"));
	DetectionComp = CreateDefaultSubobject<UDetectionComponent>(TEXT("Detection component"));
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	BindDelegates();
	if (AttackComp && AttackArea && ChaseArea)
	{
		float Distance = AttackComp->GetAttackDistance();
		AttackArea->SetSphereRadius(Distance);
		ChaseArea->SetSphereRadius(Distance * 2);
	}
}


void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DetectionComp && DetectionComp->IsAnyoneInAttackRange())
	{
		SetActorRotation(DetectionComp->GetAttackRotation());
		if (AttackComp) AttackComp->Attack();
	}
}


void AEnemyCharacter::BindDelegates()
{
	if (HealthComp)
	{
		HealthComp->OnDeathDelegate.AddUObject(this, &AEnemyCharacter::OnDeath);
	}
	if (AttackArea && DetectionComp && ChaseArea)
	{
		DetectionComp->InitComponent(AttackArea, ChaseArea);
	}
}


void AEnemyCharacter::OnDeath()
{
	Destroy();
}


void AEnemyCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const{TagContainer = GameplayTags;}
bool AEnemyCharacter::HasMatchingGameplayTag(FGameplayTag TagToCheck) const{return GameplayTags.HasTag(TagToCheck);}