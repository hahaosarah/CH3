// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"

// Sets default values
AMovingActor::AMovingActor()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")); // 루트 컴포넌트 생성
	SetRootComponent(SceneRoot); // 루트 컴포넌트 설정

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp")); // 정적 메시 컴포넌트 생성
	StaticMeshComp->SetupAttachment(SceneRoot); // 루트 컴포넌트에 정적 메시 컴포넌트 부착

	PrimaryActorTick.bCanEverTick = true; // 매 프레임마다 Tick 함수 호출 가능하도록 설정
	MoveSpeed = 100.0f; // 이동 속도 초기화
	MoveRange = 500.0f; // 이동 범위 초기화
	MoveSign = 1.0f; // 이동 부호 초기화
	MoveWorldDirection = FVector(0.0f, 0.0f, 1.0f); // 이동 월드 방향 초기화
	HideDelay = 3.0f; // 숨김 지연 시간 초기화
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation(); // 시작 위치 저장
	GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, this, &AMovingActor::HidePlatform, HideDelay, false);
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector FromStart = CurrentLocation - StartLocation;
	FVector NormalizedDirection = MoveWorldDirection.GetSafeNormal();

	float DistanceFromStart = FVector::DotProduct(FromStart, NormalizedDirection);

	if (DistanceFromStart >= MoveRange || DistanceFromStart <= -MoveRange)
	{
		MoveSign *= -1;
	}

	FVector MoveDelta = NormalizedDirection * MoveSpeed * DeltaTime * MoveSign;

	SetActorLocation(CurrentLocation + MoveDelta);

}

void AMovingActor::HidePlatform()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

// Setter 구현
void AMovingActor::SetMoveSpeed(float Speed)
{
	MoveSpeed = Speed;
}

// Getter 구현
float AMovingActor::GetMoveSpeed()
{
	return MoveSpeed;
}

void AMovingActor::SetMoveRange(float Range)
{
	MoveRange = Range;
}

float AMovingActor::GetMoveRange()
{
	return MoveRange;
}
