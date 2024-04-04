// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "MiniTank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AMiniTank : public ABasePawn
{
	GENERATED_BODY()

public:

	AMiniTank();

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 300.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MoveRange = 300.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float SpeedMoveTank = 100.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;

	void CheckFireCondition(); 
	//void CheckMoveCondition();

	bool InFireRange();
	bool InMoveRange();

	void Move(float DeltaTime);

};
