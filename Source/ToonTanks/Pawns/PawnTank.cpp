#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();
    PlayerControllerRef = GetController<APlayerController>();
}

void APawnTank::HandleDestruction() 
{
    // Call parent class first to handle general destruction tasks
    Super::HandleDestruction();    
	// TODO: Inform the GameMode that the Player died
	// TODO: Hide() all components and stop movement input
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Rotate();
    Move();

    if (PlayerControllerRef) 
    {
        FHitResult TraceHitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
        FVector HitLocation = TraceHitResult.ImpactPoint;
        RotateTurret(HitLocation);
    }
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float AxisValue) 
{
    // Apply all movement in the X (forward) direction
    MoveDirection = FVector(AxisValue * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float AxisValue) 
{
    // Create a value representing our desired delta rotation this frame
    float RotateAmount = AxisValue * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    // Create a Rotator, putting our value in the Z (Yaw) axis
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    // Transform into a Quaternion
    RotationDirection = FQuat(Rotation);
}

// Perform the actual move using calculated values
void APawnTank::Move() 
{
    AddActorLocalOffset(MoveDirection, true);
}

// Perform the actual rotation using calculated values
void APawnTank::Rotate() 
{
    AddActorLocalRotation(RotationDirection, true);
}