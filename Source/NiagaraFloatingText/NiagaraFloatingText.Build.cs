// © at0mic Games

using UnrealBuildTool;

public class NiagaraFloatingText : ModuleRules
{
	public NiagaraFloatingText(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		IWYUSupport = IWYUSupport.Full;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"GameplayAbilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Niagara"
		});
	}
}
