// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aims/TestAim.h"
#include "TestThirdAim.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ATestThirdAim : public ATestAim
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float RadiusTraceSphere = 200.0f;

	UPROPERTY(EditDefaultsOnly)
	float DistanceToActor = 3000.0f;

	virtual bool CanBeDamaged() override;
};
