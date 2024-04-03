// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TankPlayerController)
	{
		FHitResult HitResult;
		
		TankPlayerController->GetHitResultUnderCursor
		(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);

		DrawDebugSphere
		(
			GetWorld(),
			HitResult.ImpactPoint,
			10.f,
			12,
			FColor::Red,
			false
		);

		if (HitResult.GetActor())
		{
			//UE_LOG(LogTemp, Display, TEXT("True"));
		}
		else
		{
			//UE_LOG(LogTemp, Display, TEXT("False"));
		}

		//FVector HitResultImpactPoint = HitResult.ImpactPoint;
		//UE_LOG(LogTemp, Display, TEXT("%s"), HitResultImpactPoint.ToCompactText());

		RotateTurret(HitResult.ImpactPoint);

	}

	
}

void ATank::HandleDestruction()
{

	Super::HandleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	bAlive = false;

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);


	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);

}

void ATank::Move(float Value)
{

	FVector DeltaLocation(0.f);
	
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this); // Get Delta Time

	DeltaLocation.X = Value * Speed * DeltaTime;

	AddActorLocalOffset(DeltaLocation, true);

}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this); // Get Delta Time

	DeltaRotation.Yaw = Value * TurnRate * DeltaTime;

	AddActorLocalRotation(DeltaRotation, true);
}
