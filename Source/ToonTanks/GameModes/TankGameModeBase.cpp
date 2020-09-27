#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart();
}

void ATankGameModeBase::HandleGameStart() 
{
    // Cache any references and game win/lose conditions.
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    // Get the number of turrets in the level
    NumTurrets = GetNumberOfTurrets();
    // Call the Blueprint version of GameStart()
    GameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    // Check what type of Actor has been killed and respond accordingly
    if (DeadActor == PlayerTank) 
    {
        // If Player, go to lose state
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
    }
    // Attempt to cast our DeadActor to an APawnTurret
    else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        // If successful, we killed a Turret
        DestroyedTurret->HandleDestruction();
        // Decrement the number of turrets, end game if none are left
        if (--NumTurrets <= 0) 
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    // Check if the player destroyed all turrets
    // Show win result if they did
    // Show lose result if they didn't
    // Call the Blueprint version of GameOver(PlayerWon)
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetNumberOfTurrets() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}