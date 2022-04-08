// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestAim.h"
#include "GameFramework/SaveGame.h"
#include "TestSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UTestSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FVector, int32> SaveAimMap;
	
	
};
