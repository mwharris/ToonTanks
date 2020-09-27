#include "HealthComponent.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	// Get a reference to our custom GameMode via UGameplayStatics
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	// Bind OnTakeAnyDamage -> TakeDamage()
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) 
{
	if (Damage == 0 || Health <= 0) 
	{
		return;
	}

	Health -= Damage;

	if (Health <= 0)
	{
		if (GameModeRef) 
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("UHealthComponent::TakeDamage: No GameModeRef found!"));
		}
	} 
}