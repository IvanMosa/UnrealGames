// Fill out your copyright notice in the Description page of Project Settings.


#include "MojPlayerController.h"
#include "GameFramework/Pawn.h"

void AMojPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
    
}

void AMojPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if(bPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
        bShowMouseCursor = false;
    }
    else{
        GetPawn()->DisableInput(this);
        bShowMouseCursor = true;
    }
}