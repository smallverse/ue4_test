// Copyright Epic Games, Inc. All Rights Reserved.

#include "../Public/rust_cross_platform_lib.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

//#include "../../ThirdParty/cross_platform_lib/include/lib.rs.h"

//using namespace com::cross_platform_lib;

#include "../../ThirdParty/cross_platform_lib/include/bindings.h"

#define LOCTEXT_NAMESPACE "Frust_cross_platform_libModule"

void Frust_cross_platform_libModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("rust_cross_platform_lib")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	UE_LOG(LogTemp, Warning, TEXT("------ Frust_cross_platform_libModule::StartupModule ,%s"), ANSI_TO_TCHAR("PLATFORM_WINDOWS"));
	/*LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/cross_platform_lib/Win64/Release/cross_platform_lib.dll"));*/
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/cross_platform_lib/Win64/Release/cross_platform_lib_ffi.dll"));
#elif PLATFORM_MAC
	// PLATFORM_MAC_X86 PLATFORM_MAC_ARM64
	UE_LOG(LogTemp, Warning, TEXT("------ Frust_cross_platform_libModule::StartupModule ,%s"), ANSI_TO_TCHAR("PLATFORM_MAC"));
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/cross_platform_lib/Mac/Release/x86_64-apple-darwin/libcross_platform_lib.dylib"));

#elif PLATFORM_LINUX
	UE_LOG(LogTemp, Warning, TEXT("------ Frust_cross_platform_libModule::StartupModule ,%s"), ANSI_TO_TCHAR("PLATFORM_LINUX"));
	//	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/cross_platform_lib/Linux/Release/x86_64-unknown-linux-gnu/libcross_platform_lib.so"));

#endif // PLATFORM_WINDOWS

#if PLATFORM_WINDOWS || PLATFORM_MAC 
	//PLATFORM_ANDROID PLATFORM_IOS is not support try catch

	UE_LOG(LogTemp, Warning, TEXT("------rust_cross_platform_lib LibraryPath: %s"), *LibraryPath);
	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (ExampleLibraryHandle)
	{
		int re = add(10000, 0);
		UE_LOG(LogTemp, Warning, TEXT("------ Frust_cross_platform_libModule ,%d"), re);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("------ Frust_cross_platform_libModule ,Failed to load rust_cross_platform_lib third party library"));
	}

#endif

}

void Frust_cross_platform_libModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(Frust_cross_platform_libModule, rust_cross_platform_lib)
