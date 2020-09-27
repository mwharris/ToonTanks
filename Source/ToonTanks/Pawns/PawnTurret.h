#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess = "true"))
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess = "true"))
	float FireRange = 500.f;

	APawnTank* PlayerPawn;
	FTimerHandle FireRateTimerHandle;

	void CheckFireCondition();
	void RotateTowardsPlayer();
	float ReturnDistanceToPlayer();
	bool PlayerInFireRange();
	bool IsPlayerValid();
	
public:
	APawnTurret();
	virtual void HandleDestruction() override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
};
