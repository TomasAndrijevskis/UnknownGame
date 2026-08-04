
#include "UnknownGame/Public/Objects/HazardZone.h"
#include "Components/HealthComponent.h"
#include "Components/SphereComponent.h"


AHazardZone::AHazardZone()
{
	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = Collision;
}


void AHazardZone::BeginPlay()
{
	Super::BeginPlay();
	if (!Collision) return;
	Collision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AHazardZone::OnBeginOverlap);
	Collision->OnComponentEndOverlap.AddUniqueDynamic(this, &AHazardZone::OnEndOverlap);
}


void AHazardZone::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap %s"), *OtherActor->GetName());
	if (UHealthComponent* HealthComp = OtherActor ? OtherActor->FindComponentByClass<UHealthComponent>() : nullptr)
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(HealthComp, &UHealthComponent::ApplyDamage, Damage);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, DamageInterval, true);
		ActiveTimers.Add(OtherActor, TimerHandle);
	}
}


void AHazardZone::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnEndOverlap"));
	if (ActiveTimers.Contains(OtherActor))
	{
		GetWorld()->GetTimerManager().ClearTimer(ActiveTimers[OtherActor]);
		ActiveTimers.Remove(OtherActor);
	}
}