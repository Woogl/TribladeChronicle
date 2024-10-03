// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TcTargetingSystem : ModuleRules
{
	public TcTargetingSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"TargetingSystem",
			});
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"AIModule",
			});
	}
}
