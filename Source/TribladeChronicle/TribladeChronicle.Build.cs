// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TribladeChronicle : ModuleRules
{
	public TribladeChronicle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "ModularGameplay", "AIModule", });

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks", });
	}
}
