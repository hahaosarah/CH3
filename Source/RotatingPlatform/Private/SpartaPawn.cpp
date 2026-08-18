#include "SpartaPawn.h"
#include "SpartaPlayerController.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"

ASpartaPawn::ASpartaPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	RootComponent = CapsuleComp;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(CapsuleComp);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(CapsuleComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}


void ASpartaPawn::BeginPlay()
{
	Super::BeginPlay();

	//물리 시뮬레이션 비활성화
	CapsuleComp->SetSimulatePhysics(false);
	SkeletalMeshComp->SetSimulatePhysics(false);
}

// Called every frame
void ASpartaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tick 바닥 체크
	bIsGrounded = CheckGrounded();

	// Tick 이동
	if (!MoveInput.IsNearlyZero())
	{
		FVector Forward = GetActorForwardVector();
		FVector Right = GetActorRightVector();
		FVector Up = GetActorUpVector();

		FVector MoveDirection =
			Forward * MoveInput.X +
			Right * MoveInput.Y +
			Up * MoveInput.Z;

		MoveDirection = MoveDirection.GetClampedToMaxSize(1.0f);
		float CurrentMoveSpeed = MoveSpeed;

		if (!bIsGrounded)
		{
			CurrentMoveSpeed *= AirControlMultiplier;
		}

		FVector DeltaLocation = MoveDirection * CurrentMoveSpeed * DeltaTime;

		AddActorWorldOffset(DeltaLocation, true);
	}

	// Tick 회전
	if (!LookInput.IsNearlyZero() || !FMath::IsNearlyZero(RollInput))
	{
		FRotator DeltaRotation(
			-LookInput.Y * PitchSpeed * DeltaTime,
			LookInput.X * YawSpeed * DeltaTime,
			RollInput * RollSpeed * DeltaTime
		);

		AddActorLocalRotation(DeltaRotation);
	}

	

	// Tick 중력
	if (!bIsGrounded)
	{
		VerticalVelocity += Gravity * DeltaTime;
		FVector GravityOffset(0.0f, 0.0f, VerticalVelocity * DeltaTime);
		AddActorWorldOffset(GravityOffset, true);
	}
	else
	{
		VerticalVelocity = 0.0f;
	}
}

void ASpartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::Move
				);
			}

			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaPawn::StopMove
				);
			}

			if (PlayerController->UpDownAction)
			{
				EnhancedInput->BindAction(
					PlayerController->UpDownAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::MoveUpDown
				);
			}

			if (PlayerController->UpDownAction)
			{
				EnhancedInput->BindAction(
					PlayerController->UpDownAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaPawn::StopMoveUpDown
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::StartJump
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaPawn::StopJump
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::Look
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaPawn::StopLook
				);
			}

			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(
					PlayerController->RollAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::Roll
				);
			}

			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(
					PlayerController->RollAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaPawn::StopRoll
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::StartSprint
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaPawn::StopSprint
				);
			}
		}
	}
}


void ASpartaPawn::Move(const FInputActionValue& value)
{
	if (!Controller) return;
	FVector2D InputValue = value.Get<FVector2D>();

	MoveInput.X = InputValue.Y; // 전/후
	MoveInput.Y = InputValue.X; // 좌/우
}

void ASpartaPawn::StopMove(const FInputActionValue& value)
{
	MoveInput.X = 0.0f;
	MoveInput.Y = 0.0f;
}

void ASpartaPawn::MoveUpDown(const FInputActionValue& value)
{
	if (!Controller) return;
	float InputValue = value.Get<float>();
	MoveInput.Z = InputValue;
}

void ASpartaPawn::StopMoveUpDown(const FInputActionValue& value)
{
	MoveInput.Z = 0.0f;
}

void ASpartaPawn::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
	}
}

void ASpartaPawn::StopJump(const FInputActionValue& value)
{
}

void ASpartaPawn::Look(const FInputActionValue& value)
{
	if (!Controller) return;
	LookInput = value.Get<FVector2D>();
}

void ASpartaPawn::StopLook(const FInputActionValue& value)
{
	LookInput = FVector2D::ZeroVector;
}

void ASpartaPawn::Roll(const FInputActionValue& value)
{
	if (!Controller) return;
	RollInput = value.Get<float>();
}

void ASpartaPawn::StopRoll(const FInputActionValue& value)
{
	RollInput = 0.0f;
}

void ASpartaPawn::StartSprint(const FInputActionValue& value)
{
}

void ASpartaPawn::StopSprint(const FInputActionValue& value)
{
}

bool ASpartaPawn::CheckGrounded()
{
	FVector Start = GetActorLocation(); // 현재 위치
	FVector End = Start - FVector(0.0f, 0.0f, GroundCheckDistance); // 아래쪽 바닥 검사 끝 위치

	FHitResult HitResult; // 충돌 결과 저장 변수
	FCollisionQueryParams Params; // 충돌 옵션 설정용 변수
	Params.AddIgnoredActor(this); // 자기 자신은 무시

	// 아래로 선을 쏴서 바닥이 있는지 검사
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	return bHit; // 바닥이면 true 반환
}