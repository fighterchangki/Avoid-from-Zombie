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
	//발사체 이동을 담당하는 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UProjectileMovementComponent* movementComp;
	//충돌 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class USphereComponent* collisionComp;
	//외관 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Movement)
		class UStaticMeshComponent* bodyMeshComp;
	//총알 제거 함수
	void Die();
	//총알 속도
	UPROPERTY(EditAnywhere, Category = Settings)
		float speed = 5000;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)override;
};
