#include "PawnHunter.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
#include "TimerManager.h"

void APawnHunter::BeginPlay()
{
	Super::BeginPlay();
    // Get a reference to the player tank
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    // Get a reference to our AIController
    AIController = Cast<AAIController>(GetController());
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

    // Rotate towards the player while inside of range
    if (InFireRange) 
    {
        RotateTurret(PlayerTank->GetActorLocation());
    }
    // Move towards the player while outside of range
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("Moving To Player!"), Distance);
        // Move towards the player
        AIController->MoveToLocation(
            PlayerTank->GetActorLocation()
        );
    }
}

// Fire if the player is alive and within fire range
void APawnHunter::CheckFireCondition()
{
    if (PlayerInFireRange()) 
    {
        Fire();
    }
}

bool APawnHunter::PlayerInFireRange()
{
    if (!IsPlayerValid()) { return false; } 
    return GetDistanceToPlayer() <= FireRange;
}

float APawnHunter::GetDistanceToPlayer()
{
    if (!IsPlayerValid()) { return 0.f; } 
    return FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());
}

bool APawnHunter::IsPlayerValid()
{
    return PlayerTank && PlayerTank->GetIsPlayerAlive();
}