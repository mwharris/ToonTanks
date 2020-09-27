#include "PawnTurret.h"
#include "PawnTank.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

APawnTurret::APawnTurret() 
{ 

}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
    // Stash a reference to the player pawn (tank)
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    // Create and get a reference to a timer that will CheckFireCondition() every FireRate seconds (2 by default)
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

void APawnTurret::HandleDestruction() 
{
    // Call parent class first to handle general destruction tasks
    Super::HandleDestruction();
	// TODO: Inform the GameMode that the Turret died
    // Destroy ourselves
    Destroy();
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    RotateTowardsPlayer();
}

void APawnTurret::RotateTowardsPlayer() 
{
    // Rotate towards the player when outside of firing range?...
    if (PlayerInFireRange()) 
    {
        RotateTurret(PlayerPawn->GetActorLocation());
    }
}

// Called when our FireRate timer ticks
void APawnTurret::CheckFireCondition() 
{
    // Fire when the Player is within FireRange
    if (PlayerInFireRange())
    {
        Fire();
    }
}

bool APawnTurret::PlayerInFireRange() 
{
    if (!IsPlayerValid()) { return false; }
    return ReturnDistanceToPlayer() <= FireRange;
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if (!IsPlayerValid()) { return 0.f; }
    // Determine the distance between this turret and the player
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

bool APawnTurret::IsPlayerValid() 
{
    return PlayerPawn && PlayerPawn->GetIsPlayerAlive();
}