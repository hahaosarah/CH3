#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpartaPawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;

struct FInputActionValue;

UCLASS()
class ROTATINGPLATFORM_API ASpartaPawn : public APawn
{
	GENERATED_BODY()

public:
	ASpartaPawn();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape|Components")
	UCapsuleComponent* CapsuleComp; // 캡슐 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape|Components")
	USkeletalMeshComponent* SkeletalMeshComp; // 스켈레탈 메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape|Components")
	USpringArmComponent* SpringArmComp; // 스프링 암  컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape|Components")
	UCameraComponent* CameraComp; // 카메라 컴포넌트

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StopMove(const FInputActionValue& value);

	UFUNCTION()
	void MoveUpDown(const FInputActionValue& value);
	UFUNCTION()
	void StopMoveUpDown(const FInputActionValue& value);

	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);

	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StopLook(const FInputActionValue& value);

	UFUNCTION()
	void Roll(const FInputActionValue& value);
	UFUNCTION()
	void StopRoll(const FInputActionValue& value);

	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	// 이동 입력
	FVector MoveInput;

	// 회전 입력
	FVector2D LookInput;
	float RollInput = 0.0f;

	// 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 600.0f;

	// 회전 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float YawSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float PitchSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RollSpeed = 100.0f;


	bool bIsGrounded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	float Gravity = -980.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity")
	float GroundCheckDistance = 120.0f;

	float VerticalVelocity = 0.0f;

	UFUNCTION()
	bool CheckGrounded();

	// 공중 이동 속도 얼마나 줄일지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AirControlMultiplier = 0.4f;
};
