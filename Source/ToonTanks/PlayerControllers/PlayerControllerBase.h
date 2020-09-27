#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

// Directly receives input notifications when a button is pressed.
// Used to enable or disable player input.

UCLASS()
class TOONTANKS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	void SetPlayerEnabled(bool SetPlayerEnabled);
	
};
