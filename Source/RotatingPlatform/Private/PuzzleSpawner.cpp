// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleSpawner.h"
#include "RotatingActor.h"
#include "MovingActor.h"

// Sets default values
APuzzleSpawner::APuzzleSpawner()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")); // 루트 컴포넌트 생성
	SetRootComponent(SceneRoot); // 루트 컴포넌트 설정
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APuzzleSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (!PlatformClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlatformClass is not set!"));
			return;
	}

	for (int32 i = 0; i < SpawnCount; i++)
	{
		// 랜덤 좌표 생성
		FVector RandomLocation = FVector(
			FMath::RandRange(SpawnMinLocation.X, SpawnMaxLocation.X),
			FMath::RandRange(SpawnMinLocation.Y, SpawnMaxLocation.Y),
			FMath::RandRange(SpawnMinLocation.Z, SpawnMaxLocation.Z)
		);

		// 랜덤 회전 속도
		float RandomRotSpeed =
			FMath::RandRange(MinRotationSpeed, MaxRotationSpeed);

		// 랜덤 이동 속도
		float RandomMoveSpeed =
			FMath::RandRange(MinMoveSpeed, MaxMoveSpeed);

		// 랜덤 이동 범위
		float RandomMoveRange =
			FMath::RandRange(MinMoveRange, MaxMoveRange);

			// 발판 스폰
			AActor* SpawnedActor = 
			GetWorld()->SpawnActor<AActor>(
				PlatformClass,
				RandomLocation,
				FRotator::ZeroRotator
			);

		// 스폰된 발판에 값 설정
		if (SpawnedActor)
		{
			// RotatingActor인지 확인
			ARotatingActor* RotatingPlatform =
				Cast<ARotatingActor>(SpawnedActor);

			if (RotatingPlatform)
			{
				RotatingPlatform->SetRotationSpeed(RandomRotSpeed);
			}

			// MovingActor인지 확인
			AMovingActor* MovingPlatform =
				Cast<AMovingActor>(SpawnedActor);

			if (MovingPlatform)
			{
				MovingPlatform->SetMoveSpeed(RandomMoveSpeed);
				MovingPlatform->SetMoveRange(RandomMoveRange);
			}
		}
	}
	
}

// Called every frame
void APuzzleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

