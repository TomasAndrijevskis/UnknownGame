
#include "Character/EnemyPawn.h"
#include "Components/AttackComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DetectionComponent.h"
#include "Components/HealthComponent.h"
#include "Components/SphereComponent.h"


AEnemyPawn::AEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	AttackArea = CreateDefaultSubobject<USphereComponent>(TEXT("Attack area"));
	AttackArea->SetupAttachment(Collision);
	
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	AttackComp = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack component"));
	DetectionComp = CreateDefaultSubobject<UDetectionComponent>(TEXT("Detection component"));
}


void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	BindDelegates();
	if (AttackComp && AttackArea) AttackArea->SetSphereRadius(AttackComp->GetAttackDistance());
}


void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DetectionComp && DetectionComp->IsAnyoneInAttackRange())
	{
		SetActorRotation(DetectionComp->GetAttackRotation());
		if (AttackComp) AttackComp->Attack();
	}
}


void AEnemyPawn::BindDelegates()
{
	if (HealthComp)
	{
		HealthComp->OnDeathDelegate.AddUObject(this, &AEnemyPawn::OnDeath);
	}
	if (AttackArea && DetectionComp)
	{
		DetectionComp->InitComponent(AttackArea);
	}
}


void AEnemyPawn::OnDeath()
{
	Destroy();
}