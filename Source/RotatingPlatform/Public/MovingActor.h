// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PuzzleSpawner.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class ROTATINGPLATFORM_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();

	// Setter: 값을 저장
	void SetMoveSpeed(float Speed);
	// Getter: 값을 꺼내서 반환
	float GetMoveSpeed();

	void SetMoveRange(float Range);
	float GetMoveRange();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	USceneComponent* SceneRoot; // 루트 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp; // 정적 메시 컴포넌트
	
	FVector StartLocation; // 시작 위치

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	float MoveSpeed; // 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	float MoveRange; // 이동 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	FVector MoveWorldDirection; // 이동 월드 방향

	FTimerHandle HideTimerHandle; // 숨김 타이머 핸들

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	float HideDelay;

	

	float MoveSign; // 이동 부호 (1: 양수, -1: 음수)

	virtual void BeginPlay() override; // 액터가 생성된 그 시점에 바로 호출되는 함수
	virtual void Tick(float DeltaTime) override; // 매 프레임마다 호출되는 함수
	void HidePlatform();


};
