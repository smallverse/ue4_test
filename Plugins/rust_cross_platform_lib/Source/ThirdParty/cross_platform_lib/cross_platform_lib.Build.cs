// Fill out your copyright notice in the Description page of Project Settings.
using System;
using System.IO;
using UnrealBuildTool;

public class cross_platform_lib : ModuleRules
{
	public cross_platform_lib(ReadOnlyTargetRules Target) : base(Target)
	{
		Console.WriteLine("-----------------------------------ThirdParty ModuleRules: cross_platform_lib start-------------------------------------------");
        Console.WriteLine("-----------------------------------ModuleDirectory:{0}", ModuleDirectory);
        Console.WriteLine("-----------------------------------Target.Platform:{0}", Target.Platform);

        Type = ModuleType.External;

        string includePath = Path.Combine(ModuleDirectory, "include");
        PublicIncludePaths.Add(includePath);
        Console.WriteLine("-----------------------------------includePath:{0}", includePath);

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "bcrypt.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "UserEnv.lib"));
            // Add the import library
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "cross_platform_lib.lib"));

            // Delay-load the DLL, so we can load it from the right place first
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "cross_platform_lib.dll"));

            // Ensure that the DLL is staged along with the executable
            //RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "Win64", "Release", "cross_platform_lib.dll"));
            //cross_platform_lib
            RuntimeDependencies.Add("$(BinaryOutputDir)/cross_platform_lib.dll", Path.Combine(ModuleDirectory, "Win64", "Release", "cross_platform_lib.dll"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            //m1 上构建的dylib
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "x86_64-apple-darwin", "cross_platform_lib.dylib"));
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "x86_64-apple-darwin", "cross_platform_lib.dylib"));
            // PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release","x86_64-apple-darwin", "cross_platform_lib.dylib"));
            // RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/cross_platform_lib/Mac/Release/x86_64-apple-darwin/cross_platform_lib.dylib");
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            string ExampleSoPath = Path.Combine(ModuleDirectory, "Linux", "Release", "x86_64-unknown-linux-gnu", "cross_platform_lib.so");
            PublicAdditionalLibraries.Add(ExampleSoPath);
            PublicDelayLoadDLLs.Add(ExampleSoPath);
            RuntimeDependencies.Add(ExampleSoPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Android", "include"));

            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(ModuleDirectory, "Android", "CROSS_PLATFORM_LIB_UPL.xml")));

            // select required architecture
            string Architecture = "armeabi-v7a";
            //string Architecture = "arm64-v8a";

            string soPath = Path.Combine(ModuleDirectory, "Android", "Release", Architecture, "cross_platform_lib.so");
            PublicAdditionalLibraries.Add(soPath);
            //PublicDelayLoadDLLs.Add(soPath);
            //RuntimeDependencies.Add(soPath);

            Console.WriteLine("-----------------------------------soPath:{0}", soPath);

        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
            AdditionalPropertiesForReceipt.Add(new ReceiptProperty("IOSPlugin", Path.Combine(ModuleDirectory, "IOS", "CROSS_PLATFORM_LIB_UPL.xml")));

            // select required architecture
            string Architecture = "aarch64-apple-ios";

            string soPath = Path.Combine(ModuleDirectory, "IOS", "Release", Architecture, "cross_platform_lib.a");
            PublicAdditionalLibraries.Add(soPath);
            //PublicDelayLoadDLLs.Add(soPath);
            //RuntimeDependencies.Add(soPath);
        }

        Console.WriteLine("-----------------------------------ThirdParty ModuleRules: cross_platform_lib end-------------------------------------------");
	}
}
