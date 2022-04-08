// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestGameMode.h"

#include "TestHUD.h"
#include "TestCharacter.h"
#include "TestSaveGame.h"
#include "Kismet/GameplayStatics.h"

ATestGameMode::ATestGameMode()
	: Super()
{
	DefaultPawnClass = ATestCharacter::StaticClass();

	// use our custom HUD class
	HUDClass = ATestHUD::StaticClass();
}

void ATestGameMode::SortAims()
{
	CurrentAims.Sort([](const ATestAim& Aim1, const ATestAim& Aim2)
	{
		return Aim1.GetCurrentHP() < Aim2.GetCurrentHP();
	});
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATestAim::StaticClass(), StartAims);
	
	for(const auto StartAim : StartAims)
	{
		const auto Aim = Cast<ATestAim>(StartAim);
		if(!Aim) continue;
		CurrentAims.Add(Aim);
	}
	
	LoadGame();
	
	
	
}


void ATestGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	

}

void ATestGameMode::SaveGame()
{
	UTestSaveGame* TestSaveGame = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));

	for (const auto Aim : CurrentAims)
	{
		TestSaveGame->SaveAimMap.Add(Aim->GetActorLocation(), Aim->GetCurrentHP());
	}

	UGameplayStatics::SaveGameToSlot(TestSaveGame, SaveSlotString, 0);
}

void ATestGameMode::LoadGame()
{
	UTestSaveGame* TestSaveGame = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));
	if(!TestSaveGame) return;
	
	TestSaveGame = Cast<UTestSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotString, 0));
	if(!TestSaveGame) return;

	if(TestSaveGame->SaveAimMap.Num() <= 0) return;

	for (int i = 0; i < CurrentAims.Num();)
	{
		const int32 Health = TestSaveGame->SaveAimMap.FindRef(CurrentAims[i]->GetActorLocation());

		if(Health <= 0)
		{
			const auto DeleteAim = CurrentAims[i];
			CurrentAims[i]->Destroy();
			CurrentAims.Remove(DeleteAim);
		}
		else
		{
			CurrentAims[i]->SetCurrentHP(Health);
			++i;
		}
	}
	
}

void ATestGameMode::ResetLevel()
{
	for(const auto StartAim : StartAims)
	{
		const auto Aim = Cast<ATestAim>(StartAim);
		if(!Aim) continue;
		
		if(StartAim->IsActorBeingDestroyed())
		{
			const auto SpawnAim = GetWorld()->SpawnActor<ATestAim>(Aim->GetClass(), Aim->GetActorTransform());
			if(!SpawnAim) continue;
			
			CurrentAims.Add(SpawnAim);
		}
		else
		{
			Aim->SetCurrentHP(Aim->GetMaxHP());
		}
	}
}
