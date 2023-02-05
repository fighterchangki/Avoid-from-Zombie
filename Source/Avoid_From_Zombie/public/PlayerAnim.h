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
	//플레이어 이동 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float speed = 0;
	//플레이어 좌우 이동 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		float direction = 0;
	
	//매 프레임 갱신되는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

	//플레이어가 공중에 있는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
		bool isInAir = false;
	//재생할 공격 애니메이션 몽타주
	UPROPERTY(EditDefaultsOnly, Category = PlayerAnim)
		class UAnimMontage* attackAnimMontage;
	//공격 애니메이션 함수
	void PlayAttackAnim();

	
	//회전 함수
	UFUNCTION(BlueprintCallable,Category = "Turn")
		void Turn();
	//플레이어 이동속도 애니메이션 버전
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
