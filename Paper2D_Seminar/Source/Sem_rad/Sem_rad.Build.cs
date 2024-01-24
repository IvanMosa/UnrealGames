// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sem_rad : ModuleRules
{
	public Sem_rad(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Niagara" });
	}
}
