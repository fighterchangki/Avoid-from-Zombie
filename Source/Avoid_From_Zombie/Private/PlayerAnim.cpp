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
	//�÷��̾��� �̵� �ӵ��� ������ speed�� �Ҵ��ϰ� �ʹ�
	//1.���� �� ������
	auto ownerPawn = TryGetPawnOwner();
	//2. �÷��̾�� ĳ�����ϱ�
	auto player = Cast<ATPSPlayer>(ownerPawn);
	// ĳ���� �����ߴٸ�
	if (player)
	{
		//3. �̵� �ӵ��� �ʿ�
		FVector velocity = player->GetVelocity();
		//4. �÷��̾��� ���� ���� �ʿ�
		FVector forwardVector = player->GetActorForwardVector();
		//5. speed�� ��(����) �Ҵ��ϱ�
		speed = FVector::DotProduct(forwardVector, velocity);
		//6. �¿� �ӵ� �Ҵ��ϱ�
		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);
		//�÷��̾ ���� ���߿� �ִ��� ���θ� ����ϰ� �ʹ�.
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
