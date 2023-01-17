// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Bullet.h"
#include<Blueprint/UserWidget.h>
// Sets default values
ATPSPlayer::ATPSPlayer() 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	//TEXT("!!!!!!!!!!!!!!!!!!!Hello World");
	if (TempMesh.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hello!!!!!!!!!!!"));
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
	gunMeshComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempGunMesh(TEXT("SkeletalMesh'/Game/Weapon/Mesh/SK_FPGun.SK_FPGun'"));
	if (TempGunMesh.Succeeded())
	{
		gunMeshComp->SetSkeletalMesh(TempGunMesh.Object);
		gunMeshComp->SetRelativeLocation(FVector(-14, 52, 120));
	}
	//5. 스나이퍼건 컴포넌트 등록
	sniperGunComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperGunComp"));
	//5-2,부모 컴포넌트를 Mesh 컴포넌트를 설정
	sniperGunComp->SetupAttachment(GetMesh());
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempSniperMesh(TEXT("StaticMesh'/Game/SniperGun/sniper1.sniper1'"));
	//5-3.데이터로드가 성공했다면
	if (TempSniperMesh.Succeeded())
	{
		//5-4. 스태틱 메시 할당
		sniperGunComp->SetStaticMesh(TempSniperMesh.Object);
		//5-5. 위치 조정하기
		sniperGunComp->SetRelativeLocation(FVector(-22,55,120));
		//5-6. 크기 조정하기
		sniperGunComp->SetRelativeScale3D(FVector(0.15f));
	}
}
// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	//1.스나이퍼 UI 위젯 인스턴스 생성
	_sniperUI = CreateWidget(GetWorld(), sniperUIFactory);
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
	FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
	GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
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
	bUsinGrenadeGun = true;
	sniperGunComp->SetVisibility(true);
	gunMeshComp->SetVisibility(false);
}

