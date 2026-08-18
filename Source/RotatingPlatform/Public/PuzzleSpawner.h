// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleSpawner.generated.h"

UCLASS()
class ROTATINGPLATFORM_API APuzzleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleSpawner();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	USceneComponent* SceneRoot; // 루트 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int32 SpawnCount; // 스폰 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	FVector SpawnMinLocation; // 랜덤 최소 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	FVector SpawnMaxLocation; // 랜덤 최대 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	float MinRotationSpeed; // 최소 회전 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	float MaxRotationSpeed; // 최대 회전 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	float MinMoveSpeed; // 최소 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	float MaxMoveSpeed; // 최대 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	float MinMoveRange; // 최소 이동 범위 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	float MaxMoveRange; // 최대 이동 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	float MinAngle; // 최소 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Location")
	float MaxAngle; // 최대 각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Class")
	TSubclassOf<AActor> PlatformClass; // 스폰할 발판 클래스


	virtual void BeginPlay() override; // 액터가 생성된 그 시점에 바로 호출되는 함수
	virtual void Tick(float DeltaTime) override; // 매 프레임마다 호출되는 함수
};
