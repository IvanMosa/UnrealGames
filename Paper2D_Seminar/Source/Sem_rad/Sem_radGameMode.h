// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Sem_radGameMode.generated.h"

UCLASS(minimalapi)
class ASem_radGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASem_radGameMode();

	UFUNCTION(BlueprintCallable, Category = "UMG")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time")
    int32 TimerCount = 0;

    UFUNCTION(BlueprintCallable)
    int32 GetTimerCount();

    
    FTimerHandle MyTimerHandle;
    
    void OnTimer();

    void GameOver();

protected:

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG")
    TSubclassOf<UUserWidget> NameTagWidget;

    UPROPERTY(EditAnywhere, Category = "UMG")
    TSubclassOf<UUserWidget> EndGameWidget;

    UPROPERTY(EditAnywhere, Category = "UMG")
    TSubclassOf<UUserWidget> GameWidget;

    UPROPERTY(EditAnywhere, Category = "UMG")
    TSubclassOf<UUserWidget> SetNameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
    TSubclassOf<UUserWidget> StartingWidgetClass;

	
    UPROPERTY()
    UUserWidget* CurrentWidget;

};



