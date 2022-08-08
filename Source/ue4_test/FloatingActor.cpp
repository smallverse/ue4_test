// Fill out your copyright notice in the Description page of Project Settings.
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FloatingActor.h"

//#include "../../Plugins/rust_cross_platform_lib/Source/ThirdParty/cross_platform_lib/include/lib.rs.h"
#include "../../Plugins/rust_cross_platform_lib/Source/ThirdParty/cross_platform_lib/include/bindings.h"



// Sets default values
AFloatingActor::AFloatingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

}

void AFloatingActor::TestLib(float DeltaTime)
{
#if PLATFORM_WINDOWS || PLATFORM_MAC 

	/*int re = com::cross_platform_lib::add(10000, 0);
	UE_LOG(LogTemp, Warning, TEXT("------add  ,%d"), re);
	FString reFS = FString::FromInt(re);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *reFS);

	::rust::String s = com::cross_platform_lib::gen_obj_info_str("11", 11, "11");
	FString fs(s.c_str());
	UE_LOG(LogTemp, Warning, TEXT("------gen_obj_info_str,%s"), *fs);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *fs);

	com::cross_platform_lib::ObjInfo info = com::cross_platform_lib::gen_obj_info("22", 22, "22");
	FString fsName(info.name.c_str());
	UE_LOG(LogTemp, Warning, TEXT("------gen_obj_info,%s"), *fsName);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *fsName);

	com::cross_platform_lib::Quaternion q = com::cross_platform_lib::gen_quaternion(DeltaTime, 0.0, 0.0, 0.0);
	UE_LOG(LogTemp, Warning, TEXT("------gen_quaternion,%d"), q.x);
	FString reQX = FString::SanitizeFloat(q.x);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *reQX);*/
#endif

#if PLATFORM_WINDOWS || PLATFORM_MAC ||PLATFORM_ANDROID || PLATFORM_IOS
	int c_re = add(1, 1);
	UE_LOG(LogTemp, Warning, TEXT("------c add  ,%d"), c_re);
	FString creFS = FString::FromInt(c_re);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *creFS);

	char* objs = gen_obj_info_str("22", 22, "22");
	FString cfs(objs);
	UE_LOG(LogTemp, Warning, TEXT("------c gen_obj_info_str,%s"), *cfs);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *cfs);
	gen_obj_info_str_free(objs);

	PubObjInfo* pub_info = gen_obj_info("22", 22, "22");
	FString cfsName(pub_info->name);
	UE_LOG(LogTemp, Warning, TEXT("------c gen_obj_info,%s"), *cfsName);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *cfsName);
	gen_obj_info_free(pub_info);

	PubQuaternion cq = gen_quaternion(DeltaTime, 0.0, 0.0, 0.0);
	UE_LOG(LogTemp, Warning, TEXT("------c gen_quaternion,%d"), cq.x);
	FString creQX = FString::SanitizeFloat(cq.x);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *creQX);

#endif

}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TestLib(DeltaTime);

	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

