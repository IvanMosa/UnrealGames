// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sem_radGameMode.h"
#include "TimerManager.h"
#include "Misc/FileHelper.h"
#include "Paths.h"
#include "MojPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ASem_radGameMode::ASem_radGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Users/mosa21/Documents/Unreal Projects/Sem_rad/Content/BP_Glavni_lik"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void ASem_radGameMode::GameOver()
{
    AMojPlayerController* Pawn = (AMojPlayerController*)UGameplayStatics::GetPlayerController(this,0);
    Pawn->SetPlayerEnabledState(false);
    ChangeMenuWidget(EndGameWidget);

    GetWorld()->GetTimerManager().PauseTimer(MyTimerHandle);

    FString FilePath = TEXT("/Users/mosa21/Documents/Unreal Projects/Sem_rad/Source/vrijeme.txt");
    FString FileContent = FString::Printf(TEXT("Vrijeme potrebno za skupiti 3 novcica: %ds\n"), TimerCount);
    FFileHelper::SaveStringToFile(FileContent, *FilePath);
}

void ASem_radGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    ChangeMenuWidget(StartingWidgetClass);

    GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &ASem_radGameMode::OnTimer, 1.0f, true);
}

void ASem_radGameMode::OnTimer()
{
    ++TimerCount;
}

int32 ASem_radGameMode::GetTimerCount()
{
    return TimerCount;
}
void ASem_radGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromParent();
        CurrentWidget = nullptr;
    }
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}