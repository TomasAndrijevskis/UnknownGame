
#include "Character/EnemyPawn.h"
#include "Components/AttackComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HealthComponent.h"


AEnemyPawn::AEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack component"));
}


void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	BindDelegates();
}


void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AttackComp) AttackComp->Attack();
}


void AEnemyPawn::BindDelegates()
{
	if (HealthComp)
	{
		HealthComp->OnDeathDelegate.AddUObject(this, &AEnemyPawn::OnDeath);
	}
}


void AEnemyPawn::OnDeath()
{
	Destroy();
}

