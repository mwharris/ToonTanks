#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Update the rotation of Turret Mesh to point at the LookAtTarget (called from PawnTank and PawnTurret)
void APawnBase::RotateTurret(FVector LookAtTarget) 
{
	// Create a version of LookAtTarget disregarding changes on the Z (up) axis
	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();
	// Subtract our LookAtTarget from our Location to get the vector pointing from Turret->LookAt
	FRotator Rotator = FVector(LookAtTargetClean - StartLocation).Rotation();
	// Update our Rotation to match this vector
	TurretMesh->SetWorldRotation(Rotator);
}

void APawnBase::Fire() 
{
	if (ProjectileClass) 
	{
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rotator = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotator);
		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction() 
{
	// --- Shared ---
	// Play death particles, sound, and camera shake
}