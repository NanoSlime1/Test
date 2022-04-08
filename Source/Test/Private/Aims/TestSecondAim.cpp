// Fill out your copyright notice in the Description page of Project Settings.


#include "Aims/TestSecondAim.h"

#include "Kismet/GameplayStatics.h"

bool ATestSecondAim::CanBeDamaged()
{
	const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(!Player) return false;

	const auto TestCharacter = Cast<ATestCharacter>(Player);
	const auto TraceActor = TestCharacter->TraceToActor(DistanceToAimedPlayer);

	if(TraceActor == this)
	{
		return true;
	}
	return false;
}
