// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "TPSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
//#include <Runtime/Engine/Private/KismetMathLibrary.cpp>
void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	time = DeltaSeconds;
	//플레이어의 이동 속도를 가져와 speed에 할당하고 싶다
	//1.소유 폰 얻어오기
	auto ownerPawn = TryGetPawnOwner();
	//2. 플레이어로 캐스팅하기
	auto player = Cast<ATPSPlayer>(ownerPawn);
	// 캐스팅 성공했다면
	if (player)
	{
		//3. 이동 속도가 필요
		FVector velocity = player->GetVelocity();
		//4. 플레이어의 전방 벡터 필요
		FVector forwardVector = player->GetActorForwardVector();
		//5. speed에 값(내적) 할당하기
		speed = FVector::DotProduct(forwardVector, velocity);
		//6. 좌우 속도 할당하기
		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);
		//플레이어가 현재 공중에 있는지 여부를 기억하고 싶다.
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();


		/*pawn = Cast<ATPSPlayer>(TryGetPawnOwner());
		FRotator controlRotator= pawn->GetControlRotation();
		FRotator ActorRotator = pawn->GetActorRotation();
		FRotator rtemp = ActorRotator - controlRotator;
		rtemp.NormalizeAxis();
		FRotator ctemp = FRotator(0, rootPitch, rootYaw);
		FRotator target = FMath::RInterpTo(ctemp, rtemp, time, 15);
		rootPitch =FMath::ClampAngle(target.Euler().Y, -90, 90);
		rootYaw = FMath::ClampAngle(target.Euler().Z, -90, 90);

		UE_LOG(LogTemp, Warning, TEXT("rootYaw, %f"), rootYaw);
		UE_LOG(LogTemp, Warning, TEXT("rootPitch, %f"), rootPitch);*/
		Turn();
	}
}
void UPlayerAnim::PlayAttackAnim()
{
	Montage_Play(attackAnimMontage);
}

void UPlayerAnim::Turn()
{
	actor = Cast<ATPSPlayer>(TryGetPawnOwner());
	pawn = Cast<ATPSPlayer>(TryGetPawnOwner());
	rootPitch = pawn->APawn::GetBaseAimRotation().Euler().Y;
	UE_LOG(LogTemp, Warning, TEXT("rootPitch, %f"), rootPitch);
	if (speed > 0)
	{
		rootYaw = 0;
		characterYaw = actor->GetActorRotation().Euler().Z;
		prevCharacterYaw = characterYaw;
	}
	else
	{
		prevCharacterYaw = characterYaw;
		FRotator ActorRotator = actor->GetActorRotation();
		characterYaw = ActorRotator.Euler().Z;
		float rtemp = rootYaw-(prevCharacterYaw - characterYaw);
		rootYaw = UKismetMathLibrary::NormalizeAxis(rtemp);
	}
	
}
