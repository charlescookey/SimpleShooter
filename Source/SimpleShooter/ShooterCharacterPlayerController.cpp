// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterPlayerController.h"
#include "Blueprint/UserWidget.h"


void AShooterCharacterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus , bIsWinner);
    if(CrossHair){
        CrossHair->RemoveFromViewport();
    }
    if(bIsWinner){
        UUserWidget*  WinScreen = CreateWidget(this , WinScreenClass);
        if(WinScreen){
            WinScreen->AddToViewport();
        }        
    }else{
        UUserWidget*  LoseScreen = CreateWidget(this , LoseScreenClass);
        if(LoseScreen){
            LoseScreen->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer ,this , &APlayerController::RestartLevel , RestartDelay);
}

void AShooterCharacterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    CrossHair = CreateWidget(this , CrossHairClass);
    if(CrossHair){
        CrossHair->AddToViewport();
    }
}
