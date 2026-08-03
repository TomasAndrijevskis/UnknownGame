
#pragma once

#include "CoreMinimal.h"
#include "Data/EEndgameResults.h"
#include "Subsystems/Subsystem.h"
#include "CollectibleSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTargetReached)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCountChanged, int, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCompleted, EEndgameResults);
UCLASS()
class UNKNOWNGAME_API UCollectibleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void ReportCollected();

	bool IsTargetReached() const;

	int GetCount() const;

	int GetTarget() const;
	
	FOnTargetReached OnTargetReachedDelegate;

	FOnCountChanged OnCountChangedDelegate;

	FOnCompleted OnCompletedDelegate;
	
private:
	
	bool CanAdd() const;
	
	UPROPERTY(VisibleAnywhere)
	int Count = 0;

	UPROPERTY(VisibleAnywhere)
	int Target = 3;
};
