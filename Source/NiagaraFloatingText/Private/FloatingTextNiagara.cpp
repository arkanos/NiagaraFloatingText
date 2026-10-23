// © at0mic Games

#include "FloatingTextNiagara.h"

#include "NiagaraComponent.h"

namespace
{
	int32 GlyphFromChar(TCHAR Character)
	{
		if (Character >= '0' && Character <= '9')
		{
			return Character - '0';
		}

		/* Map characters to glyphs.
		 * Order here doesn't matter as long as it has an enum map
		 */
		switch (Character)
		{
			/* Special characters*/
			case '+': return (int32)FloatingText::EGlyph::Plus;
			case '!': return (int32)FloatingText::EGlyph::Exclamation;
			case '?': return (int32)FloatingText::EGlyph::Question;
			case ' ': return (int32)FloatingText::EGlyph::Space;
			/* Uppercase characters*/
			case 'A': return (int32)FloatingText::EGlyph::A;
			case 'B': return (int32)FloatingText::EGlyph::B;
			case 'C': return (int32)FloatingText::EGlyph::C;
			case 'D': return (int32)FloatingText::EGlyph::D;
			case 'E': return (int32)FloatingText::EGlyph::E;
			case 'F': return (int32)FloatingText::EGlyph::F;
			case 'G': return (int32)FloatingText::EGlyph::G;
			case 'H': return (int32)FloatingText::EGlyph::H;
			case 'I': return (int32)FloatingText::EGlyph::I;
			case 'J': return (int32)FloatingText::EGlyph::J;
			case 'K': return (int32)FloatingText::EGlyph::K;
			case 'L': return (int32)FloatingText::EGlyph::L;
			case 'M': return (int32)FloatingText::EGlyph::M;
			case 'N': return (int32)FloatingText::EGlyph::N;
			case 'Ñ': return (int32)FloatingText::EGlyph::Ñ;
			case 'O': return (int32)FloatingText::EGlyph::O;
			case 'P': return (int32)FloatingText::EGlyph::P;
			case 'Q': return (int32)FloatingText::EGlyph::Q;
			case 'R': return (int32)FloatingText::EGlyph::R;
			case 'S': return (int32)FloatingText::EGlyph::S;
			case 'T': return (int32)FloatingText::EGlyph::T;
			case 'U': return (int32)FloatingText::EGlyph::U;
			case 'V': return (int32)FloatingText::EGlyph::V;
			case 'W': return (int32)FloatingText::EGlyph::W;
			case 'X': return (int32)FloatingText::EGlyph::X;
			case 'Y': return (int32)FloatingText::EGlyph::Y;
			case 'Z': return (int32)FloatingText::EGlyph::Z;
			/* Lowercase characters*/
			case 'a': return (int32)FloatingText::EGlyph::a;
			case 'b': return (int32)FloatingText::EGlyph::b;
			case 'c': return (int32)FloatingText::EGlyph::c;
			case 'd': return (int32)FloatingText::EGlyph::d;
			case 'e': return (int32)FloatingText::EGlyph::e;
			case 'f': return (int32)FloatingText::EGlyph::f;
			case 'g': return (int32)FloatingText::EGlyph::g;
			case 'h': return (int32)FloatingText::EGlyph::h;
			case 'i': return (int32)FloatingText::EGlyph::i;
			case 'j': return (int32)FloatingText::EGlyph::j;
			case 'k': return (int32)FloatingText::EGlyph::k;
			case 'l': return (int32)FloatingText::EGlyph::l;
			case 'm': return (int32)FloatingText::EGlyph::m;
			case 'n': return (int32)FloatingText::EGlyph::n;
			case 'ñ': return (int32)FloatingText::EGlyph::ñ;
			case 'o': return (int32)FloatingText::EGlyph::o;
			case 'p': return (int32)FloatingText::EGlyph::p;
			case 'q': return (int32)FloatingText::EGlyph::q;
			case 'r': return (int32)FloatingText::EGlyph::r;
			case 's': return (int32)FloatingText::EGlyph::s;
			case 't': return (int32)FloatingText::EGlyph::t;
			case 'u': return (int32)FloatingText::EGlyph::u;
			case 'v': return (int32)FloatingText::EGlyph::v;
			case 'w': return (int32)FloatingText::EGlyph::w;
			case 'x': return (int32)FloatingText::EGlyph::x;
			case 'y': return (int32)FloatingText::EGlyph::y;
			case 'z': return (int32)FloatingText::EGlyph::z;

			default:
				return (int32)FloatingText::EGlyph::Invalid;
		}
	}
}

FloatingText::FFloatingTextGlyphData FloatingText::EncodeGlyphs(const FString& Text)
{
	FFloatingTextGlyphData Result;

	Result.CharacterCount = FMath::Min(Text.Len(), MaxGlyphs);

	for (int32 Index = 0; Index < Result.CharacterCount; ++Index)
	{
		Result.Glyphs[Index] = GlyphFromChar(Text[Index]);
	}

	return Result;
}

void FloatingText::ApplyToNiagara(UNiagaraComponent* NiagaraComponent, const FFloatingTextStyle& Style, const FFloatingTextGlyphData& GlyphData)
{
	if (!NiagaraComponent)
	{
		return;
	}

	NiagaraComponent->SetVariableFloat(TEXT("User.InSize"), Style.Size);
	NiagaraComponent->SetVariableFloat(TEXT("User.InSpacing"), Style.Spacing);
	NiagaraComponent->SetVariableLinearColor(FName(TEXT("User.Color")), Style.Color);
	NiagaraComponent->SetVariableInt(TEXT("User.CharacterCount"), GlyphData.CharacterCount);

	for (int32 Index = 0; Index < MaxGlyphs; ++Index)
	{
		NiagaraComponent->SetVariableInt(*FString::Printf(TEXT("User.Char%d"), Index), GlyphData.Glyphs[Index]);
	}
}

void FloatingText::ApplyToNiagara(UNiagaraComponent* NiagaraComponent, const FFloatingTextStyle& Style)
{
	ApplyToNiagara(NiagaraComponent, Style, EncodeGlyphs(Style.Text.ToString()));
}
