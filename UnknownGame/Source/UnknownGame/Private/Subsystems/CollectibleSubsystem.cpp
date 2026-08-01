
#include "Subsystems/CollectibleSubsystem.h"


void UCollectibleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}


void UCollectibleSubsystem::ReportCollected()
{
	if (!CanAdd()) return;
	Count++;
	OnCountChangedDelegate.Broadcast(Count, Target);
	if (Count == Target)
	{
		OnTargetReachedDelegate.Broadcast();
	}
}


bool UCollectibleSubsystem::IsTargetReached() const {return Count >= Target;}
bool UCollectibleSubsystem::CanAdd() const {return Count < Target;}
int UCollectibleSubsystem::GetCount() const{return Count;}
int UCollectibleSubsystem::GetTarget() const{return Target;}