// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class AVOID_FROM_ZOMBIE_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	//�÷��̾� �̵� �ӵ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float speed = 0;
	//�÷��̾� �¿� �̵� �ӵ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float direction = 0;
	
	//�� ������ ���ŵǴ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

	//�÷��̾ ���߿� �ִ��� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		bool isInAir = false;
	//����� ���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category = PlayerAnim)
		class UAnimMontage* attackAnimMontage;
	//���� �ִϸ��̼� �Լ�
	void PlayAttackAnim();

	
	//ȸ�� �Լ�
	UFUNCTION(BlueprintCallable,Category = "Turn")
		void Turn();
	//�÷��̾� �̵��ӵ� �ִϸ��̼� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float fspeed;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float movementOffsetYaw();*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float characterYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float prevCharacterYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rootYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rootPitch;
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float rootPitch;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float time;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		AActor* actor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		APawn* pawn;
};
