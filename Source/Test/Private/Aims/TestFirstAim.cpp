// Fill out your copyright notice in the Description page of Project Settings.


#include "Aims/TestFirstAim.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

bool ATestFirstAim::CanBeDamaged()
{
	const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(!Player) return false;
	
	const float Distance = FVector::Dist(Player->GetActorLocation(), GetActorLocation());
	return Distance <= DistanceToFire;
}
