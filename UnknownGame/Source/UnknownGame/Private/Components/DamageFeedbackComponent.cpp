
#include "Components/DamageFeedbackComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UDamageFeedbackComponent::OnDamageReceived(float CurrentHealth, float MaxHealth, float Delta)
{
	if (Delta < 0.f)
	{
		if (ACharacter* Owner = Cast<ACharacter>(GetOwner()))
		{
			FVector3d ForwardVector = Owner->GetActorForwardVector();
			if (UCharacterMovementComponent* MovComp = Owner->GetCharacterMovement())
			{
				MovComp->AddImpulse(-ForwardVector * StrengthMultiplier, true);
			}
		}
	}
}
