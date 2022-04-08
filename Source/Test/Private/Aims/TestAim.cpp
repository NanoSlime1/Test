// Fill out your copyright notice in the Description page of Project Settings.


#include "Aims/TestAim.h"

#include "SortTask.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Test/TestCharacter.h"
#include "Test/TestGameMode.h"
#include "Test/TestProjectile.h"


// Sets default values
ATestAim::ATestAim()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(CollisionComponent);
	
	SphereStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Sphere");
	SphereStaticMesh->SetupAttachment(CollisionComponent);

	OnActorBeginOverlap.AddDynamic(this, &ATestAim::OnOverlapBegin);

	MaterialOnHover = CreateDefaultSubobject<UMaterialInterface>("MaterialOnHover");

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(SphereStaticMesh);
	
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
}

// Called when the game starts or when spawned
void ATestAim::BeginPlay()
{
	Super::BeginPlay();
	
	
	
	CurrentHP = MaxHealth;
	DefaultMaterial = SphereStaticMesh->GetMaterial(0);
	TextRenderComponent->SetText(FText::FromString(FString::FromInt(CurrentHP)));
}

// Called every frame
void ATestAim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(Player)
	{
		FRotator Rotator = Player->GetActorRotation();
		Rotator.Yaw += 180;

		TextRenderComponent->SetRelativeRotation(Rotator);
	}
}

void ATestAim::OnOverlapBegin(AActor* OverlapActor, AActor* OtherActor)
{
	if(!CanBeDamaged()) return;
	if(!Cast<ATestProjectile>(OtherActor)) return;
	if(!GetWorld()) return;

	const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	const auto TTCharacter = Cast<ATestCharacter>(Player);

	OtherActor->Destroy();
	OnGetDamage(TTCharacter->GetDamage());
}

void ATestAim::ChangeMaterialOnHover()
{
	SphereStaticMesh->SetMaterial(0, MaterialOnHover);
}

void ATestAim::ChangeMaterialToDefault()
{
	SphereStaticMesh->SetMaterial(0, DefaultMaterial);
}

void ATestAim::SetCurrentHP(int32 Health)
{
	CurrentHP = Health;
	TextRenderComponent->SetText(FText::FromString(FString::FromInt(CurrentHP)));
}


void ATestAim::OnGetDamage(int32 Damage)
{
	CurrentHP -= Damage;
	TextRenderComponent->SetText(FText::FromString(FString::FromInt(CurrentHP)));
	
	const auto GameMode = GetWorld()->GetAuthGameMode();
	if(!GameMode) return;

	const auto TestGameMode = Cast<ATestGameMode>(GameMode);
	if(!TestGameMode) return;
	
	(new FAutoDeleteAsyncTask<SortTask>(TestGameMode))->StartBackgroundTask();
	
	if(CurrentHP <= 0)
	{
		TestGameMode->CurrentAims.Remove(this);
		Destroy();
	}


}

