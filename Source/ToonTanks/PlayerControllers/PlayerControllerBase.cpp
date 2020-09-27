#include "PlayerControllerBase.h"
#include "GameFramework/Pawn.h"

void APlayerControllerBase::SetPlayerEnabled(bool SetPlayerEnabled) 
{
    // Enable/Disable input based on player enabled
    if (SetPlayerEnabled) 
    {
        GetPawn()->EnableInput(this);
    }
    else 
    {
        GetPawn()->DisableInput(this);
    }
    // Hide/Show the mouse cursor based on player enabled
    bShowMouseCursor = !SetPlayerEnabled;
}