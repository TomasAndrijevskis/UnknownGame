
#include "Components/DetectionComponent.h"
#include "GameplayTagAssetInterface.h"
#include "Components/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UDetectionComponent::InitComponent(UPrimitiveComponent* Component)
{
	Component->OnComponentBeginOverlap.AddUniqueDynamic(this, &UDetectionComponent::OnBeginOverlap);
	Component->OnComponentEndOverlap.AddUniqueDynamic(this, &UDetectionComponent::OnEndOverlap);
}


void UDetectionComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->FindComponentByClass<UHealthComponent>())
	{
		IGameplayTagAssetInterface* OwnerTagInterface = Cast<IGameplayTagAssetInterface>(GetOwner());
		IGameplayTagAssetInterface* EnemyTagInterface = Cast<IGameplayTagAssetInterface>(OtherActor);
		if (OwnerTagInterface && EnemyTagInterface)
		{
			FGameplayTagContainer GameplayTags;
			OwnerTagInterface->GetOwnedGameplayTags(GameplayTags);
			if (!EnemyTagInterface->HasAnyMatchingGameplayTags(GameplayTags))
			{
				DefaultRotation = GetOwner()->GetActorRotation();
				if (!Actors.Contains(OtherActor)) Actors.Add(OtherActor);
			}
		}
	}
}


void UDetectionComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Actors.Contains(OtherActor)) Actors.Remove(OtherActor);
	if (Actors.IsEmpty()) GetOwner()->SetActorRotation(DefaultRotation);
}


bool UDetectionComponent::IsAnyoneInAttackRange() const {return Actors.Num() > 0;}
FRotator UDetectionComponent::GetAttackRotation() const{return UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), Actors.Last()->GetActorLocation());}