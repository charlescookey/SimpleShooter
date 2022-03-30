// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterCharacter.h"
#include "AIController.h"


UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp , NodeMemory);

    AAIController* Controller = OwnerComp.GetAIOwner();
    if(Controller){
        AShooterCharacter* Shooter = Cast<AShooterCharacter>(Controller->GetPawn());
        if(Shooter){
            Shooter->Shoot();
            return EBTNodeResult::Succeeded;
        }
    }
    
    return EBTNodeResult::Failed;
}
