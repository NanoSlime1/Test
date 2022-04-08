// Fill out your copyright notice in the Description page of Project Settings.


#include "Aims/TestThirdAim.h"

#include "Kismet/GameplayStatics.h"
#include "Test/TestCharacter.h"

bool ATestThirdAim::CanBeDamaged()
{
	if (!GetWorld()) return false;

	const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player || !Player->Controller) return false;

	const auto TestPlayer = Cast<ATestCharacter>(Player);
	if(!TestPlayer) return false;

	TArray<FHitResult> HitResults;

	FVector StartLocation;
	FVector EndLocation;
	TestPlayer->GetTraceLocation(StartLocation, EndLocation, DistanceToActor);

	UKismetSystemLibrary::SphereTraceMulti(GetWorld(),
	                                        StartLocation,
	                                        EndLocation,
	                                        RadiusTraceSphere,
	                                        ETraceTypeQuery::TraceTypeQuery2,
	                                        true,
	                                        {Player} ,
	                                        EDrawDebugTrace::None,
	                                        HitResults,
	                                        false
	);

	for (const auto HitRes : HitResults)
	{
		if(HitRes.Actor == this)
		{
			return true;
		}
	}
	
	return false;
}
