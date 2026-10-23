# Niagara Floating Text

Spawns a Niagara floating-number effect from a **Gameplay Cue**, driven by `FGameplayCueParameters::RawMagnitude` and a small set of editable VFX properties on the cue class.

## What is included

| Path               | Assets                                                                                                                                    |
| ------------------ | ----------------------------------------------------------------------------------------------------------------------------------------- |
| `Content/Cues/`    | `GC_FloatingText` — example gameplay cue (parent: `NiagaraFloatingText_SpawnDamageText`).                                                 |
| `Content/Niagara/` | `NS_FloatingText` — Niagara system; `M_FloatingText` — parent material; `MI_FloatingText` — material instance for the sprite/atlas setup. |
| `Content/Fonts/`   | Font sources for baking or reference when building glyph atlases.                                                                         |

## Setup

1. **Edit → Plugins** → enable **Niagara Floating Text**.
2. **Project Settings → Gameplay Abilities** (Gameplay Ability System) → **Gameplay Cue Notify Paths** → add:
   ```
    /NiagaraFloatingText/Cues
   ```

    GAS only auto-discovers cue assets under paths listed here. Without this entry, cues living in the plugin `Content/Cues` folder are not registered and their tags will not resolve at runtime.

    If you are using another folder, make sure you have an entry for it as well. For example `/Game/GAS/Cues`.

    Equivalent `DefaultGame.ini` entry under `[/Script/GameplayAbilities.AbilitySystemGlobals]`:
3. Create a copy of provided Gameplay Cue asset (or create a new one parented to `NiagaraFloatingText_SpawnDamageText`).
4. By default, this asset has assigned the **Niagara Effect** `NS_FloatingText`. You can tune the spawn/font/color properties, and register the cue tag with your abilities/effects as usual for GAS. By default, is using one named `GameplayCue.Damage`.

## Default behavior

On cue execute:

1. Spawn `NiagaraEffect` at the target actor location + `SpawnPosition` with random `PositionDeviation`.
2. Build text from `RoundToInt(Parameters.RawMagnitude)` via `BuildFloatingText`.
3. Push style into the Niagara component through `FloatingText::ApplyToNiagara`.

Cue properties (category **Floating Text**): `NiagaraEffect`, `SystemScale`, `FontSize`, `FontSpacing`, `SpawnPosition`, `PositionDeviation`, `Color`.

## Advanced Customizing text and color

Override or edit `UNiagaraFloatingText_SpawnDamageText::BuildFloatingText` (see `NiagaraFloatingText_SpawnDamageText.cpp`). That function is the intended extension point.

Typical game-side patterns (not provided by the plugin):

- **Damage / hit flavor** — Add your own `FGameplayEffectContext` subclass (fire, ice, poison, critical, miss, etc.) and read it from `Parameters.EffectContext` inside `BuildFloatingText`, then set `Result.Color` and `Result.Text`.
- **Helpers** — Optional static methods on your project’s `UAbilitySystemGlobals` subclass, e.g. `IsCriticalHit(EffectContext)`, `GetDamageType(EffectContext)`.
- **Localization** — Use `LOCTEXT` / `FText::Format` for non-numeric labels:

```cpp
//--NiagaraFloatingText_SpawnDamageText.cpp
// Add this line after includes
#define LOCTEXT_NAMESPACE "FloatingText"
// Modify text with your key and default localized value
Result.Text = FText::Format(LOCTEXT("DamageText", "{0} Damage!"), FText::AsNumber(DamageAmount));
// Add this line at the end of the .cpp
#undef LOCTEXT_NAMESPACE
```

### Texture atlas grid (Sprite Renderer)

Column and row counts do not have to be equal (e.g. 10×7 is fine). The Niagara system must know how the atlas is subdivided.

In the **Sprite Renderer** module:

**Sub UV → Sub Image Size**

| Field | Meaning |
|--------|---------|
| **X** | Number of **columns** in the atlas |
| **Y** | Number of **rows** in the atlas |

If these values do not match your texture layout, glyph indices will sample the wrong tiles (wrong characters, bleeding, or garbage UVs). `User.InSize` / `User.InSpacing` from the cue control drawn size and spacing only; they do not replace **Sub Image Size**.