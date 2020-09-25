#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay() 
{
    // Cache any references and game win/lose conditions.
    // Call HandleGameStart()
}

void ATankGameModeBase::HandleGameStart() 
{
    // Initialize the start countdown, turret activation, pawn check etc
    // Call the Blueprint version of GameStart()
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    // Check if the player destroyed all turrets
    // Show win result if they did
    // Show lose result if they didn't
    // Call the Blueprint version of GameOver(PlayerWon)
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    // Check what type of Actor has been killed and respond accordingly
    // If Turret, add to score
    // If Player, go to lose state
}