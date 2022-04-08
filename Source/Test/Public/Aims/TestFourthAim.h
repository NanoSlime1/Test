// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aims/TestAim.h"
#include "TestFourthAim.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ATestFourthAim : public ATestAim
{
	GENERATED_BODY()

public:
	virtual bool CanBeDamaged() override;

	UPROPERTY(EditDefaultsOnly)
	float DistanceToFire = 3000.0f;
	
};
