#include "PawnHunter.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
#include "TimerManager.h"

void APawnHunter::BeginPlay()
{
	Super::BeginPlay();
    // Get a reference to the player tank
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    // Create and get a reference to a timer that will CheckFireCondition() every FireRate seconds (2 by default)
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APawnHunter::CheckFireCondition, FireRate, true);
}

void APawnHunter::HandleDestruction()
{
    Super::HandleDestruction();
    // Destroy ourselves
    Destroy();
}

void APawnHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    bool InFireRange = PlayerInFireRange();
    float Distance = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());
    UE_LOG(LogTemp, Warning, TEXT("Player In Fire Range: %s"), InFireRange ? TEXT("YES") : TEXT("NO"));
    UE_LOG(LogTemp, Warning, TEXT("Distance to player: %f"), Distance);

    // Rotate towards the player while inside of range
    if (InFireRange) 
    {
        RotateTurret(PlayerTank->GetActorLocation());
    }
    // Move towards the player while outside of range
    else 
    {
        // TODO: Move towards the player
    }
}

void APawnHunter::CheckFireCondition()
{
    // TODO: Check if the player is alive
    // TODO: Check if we're within fire range
    // TODO: If so, fire
}

bool APawnHunter::PlayerInFireRange()
{
    return PlayerTank && GetDistanceToPlayer() <= FireRange;
}

float APawnHunter::GetDistanceToPlayer()
{
    if (!PlayerTank) { return 0.f; } 
    return FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());
}