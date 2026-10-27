// © at0mic Games

#pragma once

#include "FloatingTextTypes.h"

class UNiagaraComponent;

namespace FloatingText
{
	NIAGARAFLOATINGTEXT_API FFloatingTextGlyphData EncodeGlyphs(const FString& Text);

	NIAGARAFLOATINGTEXT_API void ApplyToNiagara(UNiagaraComponent* NiagaraComponent, const FFloatingTextStyle& Style, const FFloatingTextGlyphData& GlyphData);
	NIAGARAFLOATINGTEXT_API void ApplyToNiagara(UNiagaraComponent* NiagaraComponent, const FFloatingTextStyle& Style);
}
