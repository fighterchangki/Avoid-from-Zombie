// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class AVOID_FROM_ZOMBIE_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//�߻�ü �̵��� ����ϴ� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* movementComp;
	//�浹 ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class USphereComponent* collisionComp;
	//�ܰ� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UStaticMeshComponent* bodyMeshComp;
};