// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FloatingActor.generated.h"

UCLASS()
class UE4_TEST_API AFloatingActor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloatingActor();


	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void TestLib(float DeltaTime);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
