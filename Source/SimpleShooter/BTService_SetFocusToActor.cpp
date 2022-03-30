// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetFocusToActor.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"


UBTService_SetFocusToActor::UBTService_SetFocusToActor()
{
    NodeName = TEXT("Set Focus To Actor");
}

void UBTService_SetFocusToActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp , NodeMemory , DeltaSeconds);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld() , 0);
    AAIController* Controller = OwnerComp.GetAIOwner();

    if(Controller && PlayerPawn){
        if(Controller->LineOfSightTo(PlayerPawn)){
            Controller->SetFocus(PlayerPawn);
        }else{
            Controller->ClearFocus(EAIFocusPriority::Gameplay);
        }
    }
}
