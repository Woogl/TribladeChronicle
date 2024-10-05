// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TribladeChronicle : ModuleRules
{
	public TribladeChronicle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"CoreUObject", 
				"Engine", 
				"GameplayTags",
				"GameplayTasks",
				"GameplayAbilities",
				"AIModule", 
				"ModularGameplay", 
				"ModularGameplayActors",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"InputCore", 
				"EnhancedInput", 
				"UMG",
				"CommonGame",
				"CommonUser",
				"TargetingSystem",
			});
	}
}
