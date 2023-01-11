// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class AVOID_FROM_ZOMBIE_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* tpsCamComp;

	void Turn(float value);
	void LookUp(float value);

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		float walkSpeed = 600;
	//이동방향
	FVector direction;
	//좌우 입력 이벤트 처리 함수
	void InputHorizontal(float value);
	//상하 이동 이벤트 처리 함수
	void InputVertical(float value);

	void InputJump();

	void Move();
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
		class USkeletalMeshComponent* gunMeshComp;
};
