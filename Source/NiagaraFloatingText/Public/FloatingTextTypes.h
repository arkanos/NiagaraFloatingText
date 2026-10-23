// © at0mic Games

#pragma once

#include "CoreMinimal.h"

namespace FloatingText
{
	struct FFloatingTextStyle
	{
		FText Text;
		FLinearColor Color;
		float Size = 32.f;
		float Spacing = 12.f;
	};
	
	/* Number of glyphs per floating text instance.
	 * Must match the number of Niagara User parameters.
	 */
	static constexpr int32 MaxGlyphs = 16;

	/* Order of glyphs must match the order of the texture atlas*/
	enum class EGlyph : int32
	{
		Num0 = 0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Plus,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		Ñ,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Exclamation,
		Question,
		a,
		b,
		c,
		d,
		e,
		f,
		g,
		h,
		i,
		j,
		k,
		l,
		m,
		n,
		ñ,
		o,
		p,
		q,
		r,
		s,
		t,
		u,
		v,
		w,
		x,
		y,
		z,
		Space,
		Invalid = -1
	};

	struct FFloatingTextGlyphData
	{
		int32 CharacterCount = 0;
		int32 Glyphs[MaxGlyphs];
		FFloatingTextGlyphData()
		{
			for (int32& Glyph : Glyphs)
			{
				Glyph = static_cast<int32>(EGlyph::Invalid);
			}
		}
	};
}
