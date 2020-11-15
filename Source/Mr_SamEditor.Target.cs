// (c) DPACK.inc

using UnrealBuildTool;
using System.Collections.Generic;

public class Mr_SamEditorTarget : TargetRules
{
	public Mr_SamEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Mr_Sam" } );
	}
}
