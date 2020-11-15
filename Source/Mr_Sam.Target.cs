// (c) DPACK.inc

using UnrealBuildTool;
using System.Collections.Generic;

public class Mr_SamTarget : TargetRules
{
	public Mr_SamTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Mr_Sam" } );
	}
}
