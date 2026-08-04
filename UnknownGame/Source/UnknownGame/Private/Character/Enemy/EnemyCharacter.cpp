
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Enemy/EnemyAIController.h"
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
	DetectAttackComp = CreateDefaultSubobject<UDetectionComponent>(TEXT("Detect attack component"));
	DetectMovementComp = CreateDefaultSubobject<UDetectionComponent>(TEXT("Detect movement component"));
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
	AIController = Cast<AEnemyAIController>(GetController());
	AcceptanceDistance = AttackComp->GetAttackDistance() / 2;
}


void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!AttackComp || !DetectMovementComp) return;
	if (DetectAttackComp->IsAnyoneInRange())
	{
		SetActorRotation(DetectAttackComp->GetLookAtRotation());
		if (AttackComp) AttackComp->Attack();
	}
	if (DetectMovementComp->IsAnyoneInRange() && AIController)
	{
		float DistanceBtwPlayerAndEnemy = FVector3d::Dist(GetActorLocation(), DetectMovementComp->GetEnemyLocation());
		if (DistanceBtwPlayerAndEnemy > AcceptanceDistance)
		{
			AIController->MoveToLocation(DetectMovementComp->GetEnemyLocation(), AcceptanceDistance);
		}
		else
		{
			AIController->StopMovement();
		}
	}
}


void AEnemyCharacter::BindDelegates()
{
	if (HealthComp)
	{
		HealthComp->OnDeathDelegate.AddUObject(this, &AEnemyCharacter::OnDeath);
	}
	if (AttackArea && DetectAttackComp)
	{
		DetectAttackComp->InitComponent(AttackArea);
	}
	if (ChaseArea && DetectMovementComp)
	{
		DetectMovementComp->InitComponent(ChaseArea);
	}
}


void AEnemyCharacter::OnDeath()
{
	Destroy();
}


void AEnemyCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const{TagContainer = GameplayTags;}
bool AEnemyCharacter::HasMatchingGameplayTag(FGameplayTag TagToCheck) const{return GameplayTags.HasTag(TagToCheck);}