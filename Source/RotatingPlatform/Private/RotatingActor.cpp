// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingActor.h"

// Sets default values
ARotatingActor::ARotatingActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")); // 루트 컴포넌트 생성
	SetRootComponent(SceneRoot); // 루트 컴포넌트 설정

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp")); // 정적 메시 컴포넌트 생성
	StaticMeshComp->SetupAttachment(SceneRoot); // 루트 컴포넌트에 정적 메시 컴포넌트 부착

	PrimaryActorTick.bCanEverTick = true; // 매 프레임마다 Tick 함수 호출 가능하도록 설정
	RotationSpeed = 90.0f; // 회전 속도 초기화 (도/초)
	CurrentTeleportIndex = 0;
	TeleportInterval = 3.0f;
	TeleportLocations.Add(FVector(0.0f, 0.0f, 100.0f));
	TeleportLocations.Add(FVector(300.0f, 0.0f, 100.0f));
	TeleportLocations.Add(FVector(300.0f, 300.0f, 100.0f));
}

// Called when the game starts or when spawned
void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &ARotatingActor::MoveToNextTeleportLocation, TeleportInterval, true);
}

// Called every frame
void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}

void ARotatingActor::MoveToNextTeleportLocation()
{   
	if (TeleportLocations.IsEmpty())
	{
		return;
	}

	SetActorLocation(TeleportLocations[CurrentTeleportIndex]);
	CurrentTeleportIndex++;

	if (CurrentTeleportIndex >= TeleportLocations.Num())
	{
		CurrentTeleportIndex = 0;
	}
}

// Setter 구현
void ARotatingActor::SetRotationSpeed(float Speed)
{
	RotationSpeed = Speed;
}

// Getter 구현
float ARotatingActor::GetRotationSpeed()
{
	return RotationSpeed;
}
