// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_RPG_20 : ModuleRules
{
	public UE_RPG_20(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Niagara"
        });

        PublicIncludePaths.Add(ModuleDirectory);
    }
}
