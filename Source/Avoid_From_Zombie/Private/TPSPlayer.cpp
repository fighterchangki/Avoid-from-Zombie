// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Bullet.h"
#include<Blueprint/UserWidget.h>
#include<Kismet/GameplayStatics.h>
#include<GameFramework/CharacterMovementComponent.h>
#include"PlayerAnim.h"
// Sets default values
ATPSPlayer::ATPSPlayer() 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	//TEXT("!!!!!!!!!!!!!!!!!!!Hello World");
	if (TempMesh.Succeeded())
	{
		
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0, 70, 90));
	springArmComp->TargetArmLength = 400;
	springArmComp->bUsePawnControlRotation = true;
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment(springArmComp);
	tpsCamComp->bUsePawnControlRotation = false;
	
	bUseControllerRotationYaw = true;
	JumpMaxCount = 2;
	GetCharacterMovement()->JumpZVelocity = 500.0f;

	gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));
	gunMeshComp->SetupAttachment(GetMesh(),TEXT("hand_rSocket"));
	UE_LOG(LogTemp, Warning, TEXT("GunMesh_Hello123!!!!!!!!!!!"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempGunMesh(TEXT("SkeletalMesh'/Game/Weapon/Mesh/SK_FPGun.SK_FPGun'"));
	if (TempGunMesh.Succeeded())
	{
		gunMeshComp->SetSkeletalMesh(TempGunMesh.Object);
		
		gunMeshComp->SetRelativeLocation(FVector(-17, 10, -3));
		gunMeshComp->SetRelativeRotation(FRotator(0, 90, 0));
		
	}
	//5. 스나이퍼건 컴포넌트 등록
	sniperGunComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperGunComp"));
	//5-2,부모 컴포넌트를 Mesh 컴포넌트를 설정
	sniperGunComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
	UE_LOG(LogTemp, Warning, TEXT("TempSniperMesh_Hello123!!!!!!!!!!!"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempSniperMesh(TEXT("StaticMesh'/Game/SniperGun/sniper1.sniper1'"));
	//5-3.데이터로드가 성공했다면
	if (TempSniperMesh.Succeeded())
	{
		//5-4. 스태틱 메시 할당
		sniperGunComp->SetStaticMesh(TempSniperMesh.Object);
		
		//5-5. 위치 조정하기
		sniperGunComp->SetRelativeLocation(FVector(-42,7,1));
		sniperGunComp->SetRelativeRotation(FRotator(0, 90, 0));
		//5-6. 크기 조정하기
		sniperGunComp->SetRelativeScale3D(FVector(0.15f));
		
	}
}
// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	//초기 속도를 걷기로 설정
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	//1.스나이퍼 UI 위젯 인스턴스 생성
	_sniperUI = CreateWidget(GetWorld(), sniperUIFactory);
	//2.일반 조준 UI크로스헤어 인스턴스 생성
	_crosshairUI = CreateWidget(GetWorld(), crosshairUIFactory);
	//3. 일반 조준 UI등록
	_crosshairUI->AddToViewport();
	//기본으로 스나이퍼건을 사용하도록 설정
	ChangeToGrenadeGun();
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	
}
void ATPSPlayer::Move()
{
	//상대 좌표방향으로 direction을 바꿔준다
	direction = FTransform(GetControlRotation()).TransformVector(direction);
	//등속 운동
	/*FVector P0 = GetActorLocation();
	FVector vt = direction * walkSpeed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);*/
	AddMovementInput(direction);
	direction = FVector::ZeroVector;
}
// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATPSPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATPSPlayer::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ATPSPlayer::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ATPSPlayer::InputVertical);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed,this, &ATPSPlayer::InputJump);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATPSPlayer::InputFire);
	PlayerInputComponent->BindAction(TEXT("GrenadeGun"), IE_Pressed, this, &ATPSPlayer::ChangeToGrenadeGun);
	PlayerInputComponent->BindAction(TEXT("SniperGun"), IE_Pressed, this, &ATPSPlayer::ChangeToSniperGun);
	PlayerInputComponent->BindAction(TEXT("Sniper"), IE_Pressed, this, &ATPSPlayer::SniperAim);
	PlayerInputComponent->BindAction(TEXT("Sniper"), IE_Released, this, &ATPSPlayer::SniperAim);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ATPSPlayer::InputRun);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &ATPSPlayer::InputRun);
}
void ATPSPlayer::SniperAim()
{
	//스나이퍼건 모드가 아니라면 처리하지 않는다
	if (bUsinGrenadeGun)
	{
		return;
	}
	//Pressed 입력 처리
	if (bSniperAim == false)
	{
		//1.스나이퍼 조준 모드 활성화
		bSniperAim = true;
		//2.스나이퍼조준 UI 등록
		_sniperUI->AddToViewport();
		//3. 카메라의 시야각 Field Of View 설정
		tpsCamComp->SetFieldOfView(45.0f);
		//4. 일반 조준 UI 제거
		_crosshairUI->RemoveFromParent();
	}
	else
	{
		//1.스나이퍼 조준 모드 비활성화
		bSniperAim = false;
		//2.스나이퍼 조준 UI 화면에서 제거
		_sniperUI->RemoveFromParent();
		//3.카메라 시야각 원래대로 복원
		tpsCamComp->SetFieldOfView(90.0f);
		//4. 일반 조준 UI 제거
		_crosshairUI->AddToViewport();
	}
}
void ATPSPlayer::Turn(float value)
{
	AddControllerYawInput(value);
}
void ATPSPlayer::LookUp(float value)
{
	AddControllerPitchInput(value);
}
void ATPSPlayer::InputHorizontal(float value)
{
	direction.Y = value;
}
void ATPSPlayer::InputVertical(float value)
{
	direction.X = value;
}
void ATPSPlayer::InputJump()
{
	Jump();
}
void ATPSPlayer::InputFire()
{
	//유탄총 사용 시
	if (bUsinGrenadeGun)
	{
		//총알 발사 처리
		FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
		GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
	}
	//스나이퍼건 사용 시
	else
	{
		//LineTrace의 시작 위치
		FVector startPos = tpsCamComp->GetComponentLocation();
		//LineTrace의 종료 위치
		FVector endPos = tpsCamComp->GetComponentLocation() + tpsCamComp->GetForwardVector() * 5000;
		//LineTrace의 충돌 정보를 담을 변수
		FHitResult hitInfo;
		//충돌 옵션 설정 변수
		FCollisionQueryParams params;
		//자기 자신(플레이어)는 충돌에서 제외
		params.AddIgnoredActor(this);
		//Channel 필터를 이용한 LineTrace충돌 검출(충돌 정보, 시작 위치, 종료 위치, 검출 채널, 충돌 옵션)
		bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);
		//LineTrace가 부딪혔을 때
		if (bHit)
		{
			//충돌 처리 -> 총알 파편 효과 발생
			//총알 파편 효과 트렌스폼
			FTransform bulletTrans;
			//부딪힌 위치 할당
			bulletTrans.SetLocation(hitInfo.ImpactPoint);
			//총알 파편 효과 인스턴스 생성
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),bulletEffectFactory, bulletTrans);
			auto hitComp = hitInfo.GetComponent();
			//1.만약 컴포넌트에 물리가 적용되어 있으면
			if (hitComp && hitComp->IsSimulatingPhysics())
			{
				//2. 날려버릴 힘과 방향
				FVector force = -hitInfo.ImpactNormal * hitComp->GetMass() * 50000;
				//3. 그 방향으로 날려버리고 싶다.
				hitComp->AddForce(force);
			}
		}
		//공격 애니메이션 재생
		auto anim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
		anim->PlayAttackAnim();
	}
}
void ATPSPlayer::ChangeToGrenadeGun()
{
	//유탄총 사용 중으로 체크
	bUsinGrenadeGun = true;
	sniperGunComp->SetVisibility(false);
	gunMeshComp->SetVisibility(true);
}
void ATPSPlayer::ChangeToSniperGun()
{
	//유탄총 사용 중으로 체크
	bUsinGrenadeGun = false;
	sniperGunComp->SetVisibility(true);
	gunMeshComp->SetVisibility(false);
}
void ATPSPlayer::InputRun()
{
	auto movement = GetCharacterMovement();
	//현재 달리기 모드라면
	if (movement->MaxWalkSpeed > walkSpeed)
	{
		//걷기 속도로 전환
		movement->MaxWalkSpeed = walkSpeed;
	}
	else
	{
		movement->MaxWalkSpeed = runSpeed;
	}
}

