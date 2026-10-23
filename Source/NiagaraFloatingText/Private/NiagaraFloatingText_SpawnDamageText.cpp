// © at0mic Games

#include "NiagaraFloatingText_SpawnDamageText.h"

#include "FloatingTextNiagara.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"

bool UNiagaraFloatingText_SpawnDamageText::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	Super::OnExecute_Implementation(MyTarget, Parameters);
	
	if (!MyTarget || !NiagaraEffect) return false;

	const FVector SpawnPos = MyTarget->GetActorLocation() + FMath::VRand()
	* PositionDeviation
	+ SpawnPosition;
	
	const FRotator SpawnRot = MyTarget->GetRootComponent()
		? MyTarget->GetRootComponent()->GetComponentRotation()
		: FRotator::ZeroRotator;
	
	UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		MyTarget->GetWorld(),
		NiagaraEffect,
		SpawnPos,
		SpawnRot,
		SystemScale,
		true,
		true
	);
       
	if (!NiagaraComponent) return false;
	
	const FloatingText::FFloatingTextStyle TextStyle = BuildFloatingText(Parameters, FontSize, FontSpacing);
	FloatingText::ApplyToNiagara(NiagaraComponent, TextStyle);
		
	return true;
}

FloatingText::FFloatingTextStyle UNiagaraFloatingText_SpawnDamageText::BuildFloatingText(
	const FGameplayCueParameters& Parameters,
	const float InFontSize,
	const float InFontSpacing) const
{
	const int32 DamageAmount = FMath::RoundToInt(Parameters.RawMagnitude);
	
	/**
	* Here you can customize the floating text style based on the damage type, hit type, or any other parameter.
	* For example, you can create your custom Gameplay Effect Context with damage types like fire, ice, poison, etc. 
	* and then use that information to set the color and text of the floating text.
	* Also you can use GameplayAbilitySystemGlobals to get the hit type and damage type flags from
	* the effect context with custom methods, like for example:
	* CustomGameplayAbilitySystemGlobals::bIsCriticalHit(Parameters.EffectContext)
	* CustomGameplayAbilitySystemGlobals::GetDamageType(Parameters.EffectContext)
	* 
	* Also, if localizable text is needed, you can use FText::Format to create the text with localization support.
	* Just make sure to add the LOCTEXT_NAMESPACE and LOCTEXT macros for localization after the includes and 
	* before the class definition.
	* 
	* Example:
	* 
	* #define LOCTEXT_NAMESPACE "FloatingText"
	* <Class methods>
	* #undef LOCTEXT_NAMESPACE
	* 
	* Then you can use FText::Format to create the text with localization support:
	* Result.Text = FText::Format(LOCTEXT("DamageText", "{0} Damage!"), FText::AsNumber(DamageAmount));
	*/
	
	FloatingText::FFloatingTextStyle Result;
	Result.Text = FText::AsNumber(DamageAmount);
	Result.Size = InFontSize;
	Result.Spacing = InFontSpacing;
	Result.Color = Color;

	return Result;
}
