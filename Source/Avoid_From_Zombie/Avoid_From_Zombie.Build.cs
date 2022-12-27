// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Avoid_From_Zombie : ModuleRules
{
	public Avoid_From_Zombie(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
