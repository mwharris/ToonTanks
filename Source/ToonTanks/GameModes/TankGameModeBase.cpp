#include "TankGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart();
    CreateScoreWidget();
}

void ATankGameModeBase::HandleGameStart() 
{
    // Cache references to player tank and player controller
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
    // Get the number of turrets in the level
    NumTurrets = GetNumberOfTurrets();
    // Call the Blueprint version of GameStart()
    GameStart();
    // Enable the player after our start countdown
    EnablePlayerAfterStart();
}

void ATankGameModeBase::EnablePlayerAfterStart()
{
    if (!PlayerControllerRef) { return; }

    // Disable the player controller until the countdown has completed
    PlayerControllerRef->SetPlayerEnabled(false);

    // Create a timer that will call a function after our StartDelay
    FTimerHandle PlayerEnableHandle;
    // FTimerDelegate bound to PlayerControllerRef, which will call SetPlayerEnabled passing true
    FTimerDelegate PlayerEnableDelegate = 
        FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabled, true);
    // Create a new timer that will call our delegate after StartDelay 
    GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    // Check what type of Actor has been killed and respond accordingly
    if (DeadActor == PlayerTank) 
    {
        // If Player, go to lose state
        PlayerTank->HandleDestruction();
        HandleGameOver(false);
        // Disable the player controller
        if (PlayerControllerRef) 
        {
            PlayerControllerRef->SetPlayerEnabled(false);
        }
    }
    // Attempt to cast our DeadActor to an APawnTurret
    else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        // If successful, we killed a Turret
        Score++;
        UpdateScoreWidget(Score);
        DestroyedTurret->HandleDestruction();
        // Decrement the number of turrets, end game if none are left
        if (--NumTurrets <= 0) 
        {
            HandleGameOver(true);
        }
    }
}

// Call the Blueprint version of GameOver(PlayerWon)
void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetNumberOfTurrets() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();
}