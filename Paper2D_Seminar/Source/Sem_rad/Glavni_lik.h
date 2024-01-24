/// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Components/WidgetComponent.h"
#include "PaperFlipbookComponent.h"
#include "Glavni_lik.generated.h"

/**
 * 
 */
UCLASS()
class SEM_RAD_API AGlavni_lik : public APaperCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Collsions")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;


	public:

		AGlavni_lik();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Counter")
	uint8 CoinAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* FallingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpRiseAnimation;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* NameTag;

	
	void Tick(float DeltaSeconds);

	void AddCoin(uint8 Value);

	protected:

		void Move(const FInputActionValue& Value);

		void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

		virtual void BeginPlay();

		uint8 GetCounter();
		
		void UpdateAnimation();

		void UpdateCharacter();

		void TraceForPlatforms();

};
