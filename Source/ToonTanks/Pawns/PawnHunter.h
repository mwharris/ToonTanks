#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "AIController.h"
#include "PawnHunter.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnHunter : public APawnBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess = "true"))
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess = "true"))
	float FireRange = 500.f;

	APawnTank* PlayerTank;
	AAIController* AIController;
	FTimerHandle FireRateTimerHandle;

	void CheckFireCondition();
	float GetDistanceToPlayer();
	bool PlayerInFireRange();
	bool IsPlayerValid();

public:
	virtual void HandleDestruction() override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};