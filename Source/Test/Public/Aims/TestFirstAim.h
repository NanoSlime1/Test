// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aims/TestAim.h"
#include "TestFirstAim.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ATestFirstAim : public ATestAim
{
	GENERATED_BODY()

public:
	virtual bool CanBeDamaged() override;

	UPROPERTY(EditDefaultsOnly)
	float DistanceToFire = 500.0f;
};
