// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aims/TestAim.h"
#include "TestSecondAim.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ATestSecondAim : public ATestAim
{
	GENERATED_BODY()


public:
	virtual bool CanBeDamaged() override;


private:
	UPROPERTY(EditDefaultsOnly)
	float DistanceToAimedPlayer = 3000.0f;
	
};
