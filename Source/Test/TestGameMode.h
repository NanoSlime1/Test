// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestGameMode.generated.h"

class ATestAim;
UCLASS(minimalapi)
class ATestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestGameMode();

	void SortAims();

	UPROPERTY(EditAnywhere)
	TArray<ATestAim*> CurrentAims;

	void SaveGame();
	
	FName GetStartLevelName() const { return StartLevelName; }

	virtual void ResetLevel() override;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> StartAims;

	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	



private:
	UPROPERTY(EditDefaultsOnly)
	FName StartLevelName = "FirstPersonExampleMap";

	FString SaveSlotString = "SaveSlot";


	void LoadGame();


	
	
};








