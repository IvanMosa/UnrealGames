// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MojPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SEM_RAD_API AMojPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void SetPlayerEnabledState(bool bPlayerEnabled);
};
