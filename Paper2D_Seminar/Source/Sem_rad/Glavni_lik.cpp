// Fill out your copyright notice in the Description page of Project Settings.


#include "Glavni_lik.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "Sem_radGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"


AGlavni_lik::AGlavni_lik(){
    
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
    CameraBoom->SetUsingAbsoluteRotation(true);
    CameraBoom->bDoCollisionTest = false;
    CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

    SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

    
    SideViewCameraComponent->bUsePawnControlRotation = false;
    SideViewCameraComponent->bAutoActivate = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;

    NameTag = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameTag"));
    NameTag->SetupAttachment(RootComponent);
    NameTag->SetRelativeLocation(FVector(0.0f, 0.0f, 50.f));
    NameTag->SetDrawSize(FVector2D(230, 55));
    
    
}

void AGlavni_lik::Move(const FInputActionValue& Value)
{

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementVector.Y);
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), MovementVector.X);
	}
}
void AGlavni_lik::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGlavni_lik::Move);


	}

}

uint8 AGlavni_lik::GetCounter()
{
    return CoinAmount;
}

void AGlavni_lik::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void AGlavni_lik::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    UpdateCharacter();

    TraceForPlatforms();

}

void AGlavni_lik::TraceForPlatforms()
{
    if(GetCharacterMovement()->IsFalling())
    {
        FHitResult Hit;

        FVector TraceStart = GetActorLocation();
        FVector TraceEnd = GetActorLocation() + (GetActorUpVector() * -1) * 100.0f;

        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(this);
        GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);


        if(Hit.bBlockingHit && GetVelocity().Z < 0.0f)
        {
            GetCapsuleComponent()->SetCollisionResponseToChannel(TraceChannelProperty, ECollisionResponse::ECR_Block);
        }
        else {
            GetCapsuleComponent()->SetCollisionResponseToChannel(TraceChannelProperty, ECollisionResponse::ECR_Overlap);
        }
    }
}

void AGlavni_lik::UpdateCharacter()
{
    UpdateAnimation();

    const FVector PlayerVelocity = GetVelocity();
    float TravelDirection = PlayerVelocity.X;

    if(Controller != nullptr)
    {
        if(TravelDirection < 0.0f)
        {
            Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
        }
        else if(TravelDirection > 0.0f)
        {
            Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
        }
    }
}

void AGlavni_lik::UpdateAnimation()
{
    const FVector PlayerVelocity = GetVelocity();
    const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

    if(GetCharacterMovement()->IsFalling())
    {
        UPaperFlipbook* DesiredAnimation = (PlayerVelocity.Z < 0.0f) ? FallingAnimation : JumpRiseAnimation;
        if(GetSprite()->GetFlipbook() != DesiredAnimation)
        {
            GetSprite()->SetFlipbook(DesiredAnimation);
        }
    }
    else
    {
        UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;
        if(GetSprite()->GetFlipbook() != DesiredAnimation)
        {
            GetSprite()->SetFlipbook(DesiredAnimation);
        }
    }

}

void AGlavni_lik::AddCoin(uint8 Value)
{
    CoinAmount += Value;

    if(CoinAmount == 3)
    {
        ASem_radGameMode* GameMode = (ASem_radGameMode*)GetWorld()->GetAuthGameMode();
        GameMode->GameOver();
    }
}