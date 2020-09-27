#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	APawnTank* PlayerTank;
	int32 NumTurrets = 0;
	APlayerControllerBase* PlayerControllerRef;
	
	// These will call our blueprint-implemented GameStart() and GameOver() appropriately.
	// So the logic on whether to start or end the game will be handled in C++ but some of the
	// trickier implementation will be handled inside of blueprints.
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);
	
	int32 GetNumberOfTurrets();
	void EnablePlayerAfterStart();

public:
	// Called by Turret or Tank.
	// Perform different actions based on which died.
	void ActorDied(AActor* DeadActor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 4;

	// Initialize everything needed to handle game mode functionality (scores, timers, etc.)
	virtual void BeginPlay() override;
	
	// We're using blueprints here because we want to implement timers and create widgets
	// This is much easier to do via Blueprints
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	// End the game in either a Win or Lose state
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

};