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

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Camera)
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
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
		TSubclassOf<class ABullet>bulletFactory;
	void InputFire();

	UPROPERTY(VisibleAnywhere, Category = GunMesh)
		class UStaticMeshComponent* sniperGunComp;
	//유탄총 사용 중인지 여부
	bool bUsinGrenadeGun = true;
	//유탄총으로 변경
	void ChangeToGrenadeGun();
	//스나이퍼건으로 변경
	void ChangeToSniperGun();
	//스나이퍼 조준
	void SniperAim();
	//스나이퍼 조준 중인지 여부
	bool bSniperAim = false;
	//스나이퍼 UI위젯 공장
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
		TSubclassOf<class UUserWidget>sniperUIFactory;
	//스나이퍼 UI 위젯 인스턴스
	class UUserWidget* _sniperUI;
	//총알 파편 효과 공장
	UPROPERTY(EditAnywhere, Category = BulletEffect)
		class UParticleSystem* bulletEffectFactory;
	//일반 조준 크로스헤어 UI위젯
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
		TSubclassOf<class UUserWidget>crosshairUIFactory;
	//크로스헤어 인스턴스
	class UUserWidget* _crosshairUI;
};
