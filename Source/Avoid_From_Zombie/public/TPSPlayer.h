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
	//�̵�����
	FVector direction;
	//�¿� �Է� �̺�Ʈ ó�� �Լ�
	void InputHorizontal(float value);
	//���� �̵� �̺�Ʈ ó�� �Լ�
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
	//��ź�� ��� ������ ����
	bool bUsinGrenadeGun = true;
	//��ź������ ����
	void ChangeToGrenadeGun();
	//�������۰����� ����
	void ChangeToSniperGun();
	//�������� ����
	void SniperAim();
	//�������� ���� ������ ����
	bool bSniperAim = false;
	//�������� UI���� ����
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
		TSubclassOf<class UUserWidget>sniperUIFactory;
	//�������� UI ���� �ν��Ͻ�
	class UUserWidget* _sniperUI;
	//�Ѿ� ���� ȿ�� ����
	UPROPERTY(EditAnywhere, Category = BulletEffect)
		class UParticleSystem* bulletEffectFactory;
	//�Ϲ� ���� ũ�ν���� UI����
	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
		TSubclassOf<class UUserWidget>crosshairUIFactory;
	//ũ�ν���� �ν��Ͻ�
	class UUserWidget* _crosshairUI;
};
