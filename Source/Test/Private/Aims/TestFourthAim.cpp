// Fill out your copyright notice in the Description page of Project Settings.


#include "Aims/TestFourthAim.h"

#include "DrawDebugHelpers.h"
#include "TestFirstAim.h"
#include "Kismet/GameplayStatics.h"
#include "Test/TestCharacter.h"

bool ATestFourthAim::CanBeDamaged()
{
	if (!GetWorld()) return false;

	const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return false;

	const auto TestPlayer = Cast<ATestCharacter>(Player);
	if (!TestPlayer) return false;

	TArray<FHitResult> HitResults;

	FVector StartLocation;
	FVector EndLocation;
	TestPlayer->GetTraceLocation(StartLocation, EndLocation, DistanceToFire);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);
	

	if(!GetWorld()->LineTraceMultiByChannel(HitResults,
	                                        StartLocation,
	                                        EndLocation,
	                                        ECC_Visibility,
	                                        CollisionParams)) return false;

	if (HitResults.GetData()[0].GetActor() == this 
	&& HitResults.GetData()[1].GetActor()->IsA(ATestFirstAim::StaticClass()))
	{
		return true;
	}

	return false;
}
