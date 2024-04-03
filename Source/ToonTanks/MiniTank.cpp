// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniTank.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

AMiniTank::AMiniTank()
{

}

void AMiniTank::BeginPlay()
{

	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AMiniTank::CheckFireCondition, FireRate, true);

}

void AMiniTank::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	
	if (Tank)
	{

		if (InFireRange())
		{
			Move(DeltaTime);
			RotateTurret(Tank->GetActorLocation());
		}

	}

}

void AMiniTank::HandleDestruction()
{

	Super::HandleDestruction();
	Destroy();

}


void AMiniTank::CheckFireCondition()
{

	if (Tank == nullptr)
	{
		return;
	}

	if (InFireRange() && Tank->bAlive)
	{
		Fire();
	}

}

bool AMiniTank::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;

}

void AMiniTank::Move(float DeltaTime)
{
	FVector Current = GetActorLocation();
	FVector Target = Tank->GetActorLocation() + (Tank->GetActorForwardVector() * 500.f);

	RotateBase(Target);
	
	SetActorLocation(FMath::VInterpConstantTo(Current, Target, DeltaTime, 100.f));

}