#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	
	// VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* LaserPointerParticle;

	FVector MoveDirection;
	FQuat RotationDirection;
	APlayerController* PlayerControllerRef;
	bool bIsPlayerAlive = true;
	UParticleSystemComponent* SpawnedLaserEmitter;
	
	// FUNCTIONS
	void CalculateMoveInput(float AxisValue);
	void CalculateRotateInput(float AxisValue);

	void Move();
	void Rotate();
	void HandleLaserPointer();

public:
	APawnTank();
	virtual void HandleDestruction() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
