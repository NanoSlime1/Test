// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Test/TestCharacter.h"
#include "TestAim.generated.h"

class ATestCharacter;
class USphereComponent;

UCLASS()
class TEST_API ATestAim : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestAim();

	virtual bool CanBeDamaged() { return  false; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SphereStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTextRenderComponent* TextRenderComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlapActor, AActor* OtherActor);

	void ChangeMaterialOnHover();
	void ChangeMaterialToDefault();

	int32 GetMaxHP() { return MaxHealth; }

	int32 GetCurrentHP() const { return CurrentHP; }
	void SetCurrentHP(int32 Health);

	

private:
	int32 CurrentHP;

	UPROPERTY()
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Materials")
	UMaterialInterface* MaterialOnHover;
	
	void OnGetDamage(int32 Damage);
};
