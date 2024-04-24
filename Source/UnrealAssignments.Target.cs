// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealAssignmentsTarget : TargetRules
{
	public UnrealAssignmentsTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;
		ExtraModuleNames.Add("UnrealAssignments");
		ExtraModuleNames.Add("Assignment1");
		ExtraModuleNames.Add("Assignment2");
	}
}
