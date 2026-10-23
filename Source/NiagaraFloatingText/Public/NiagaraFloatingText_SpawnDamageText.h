// © at0mic Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "FloatingTextTypes.h"
#include "NiagaraFloatingText_SpawnDamageText.generated.h"

class UNiagaraSystem;

UCLASS(Blueprintable)
class NIAGARAFLOATINGTEXT_API UNiagaraFloatingText_SpawnDamageText : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floating Text")
	UNiagaraSystem* NiagaraEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floating Text")
	FVector SystemScale = FVector::OneVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floating Text")
	float FontSize = 32.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floating Text")
	float FontSpacing = 16.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floating Text")
	FVector SpawnPosition = FVector(0.f, 0.f, 120.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floating Text")
	float PositionDeviation = 25.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Floating Text")
	FLinearColor Color = FLinearColor::White;
	
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
private:
	FloatingText::FFloatingTextStyle BuildFloatingText(const FGameplayCueParameters& Parameters, float InFontSize, float InFontSpacing) const;
};
