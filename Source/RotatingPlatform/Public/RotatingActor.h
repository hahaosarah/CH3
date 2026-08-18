// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PuzzleSpawner.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingActor.generated.h"

UCLASS()
class ROTATINGPLATFORM_API ARotatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingActor();
	void SetRotationSpeed(float Speed);
	float GetRotationSpeed();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	USceneComponent* SceneRoot; // 루트 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp; // 정적 메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	float RotationSpeed; // 회전 속도 (도/초)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Teleport")
	TArray<FVector> TeleportLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Teleport")
	int32 CurrentTeleportIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Teleport")
	float TeleportInterval;

	FTimerHandle TeleportTimerHandle;
	virtual void BeginPlay() override; // 액터가 생성된 그 시점에 바로 호출되는 함수
	virtual void Tick(float DeltaTime) override; // 매 프레임마다 호출되는 함수
	void MoveToNextTeleportLocation();


};
