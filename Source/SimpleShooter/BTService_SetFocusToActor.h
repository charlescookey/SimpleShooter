// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetFocusToActor.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTService_SetFocusToActor : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_SetFocusToActor();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
