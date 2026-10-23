// © at0mic Games

#pragma once

#include "FloatingTextTypes.h"

class UNiagaraComponent;

namespace FloatingText
{
	FFloatingTextGlyphData EncodeGlyphs(const FString& Text);

	void ApplyToNiagara(UNiagaraComponent* NiagaraComponent, const FFloatingTextStyle& Style, const FFloatingTextGlyphData& GlyphData);
	void ApplyToNiagara(UNiagaraComponent* NiagaraComponent, const FFloatingTextStyle& Style);
}
