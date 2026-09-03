# system — changelog

Markers: 🟢 added · 🔴 breaking · 🔵 fix · ⚪ internal or docs · 🟡 proposed
in the plan, no code written yet.

## v1.0.0

- 🟢 `Vector2/3/4`, `Matrix`, `Quaternion`, `Color`, `Constants`, `Lambdify`
- 🟢 `Rect` with **corner** semantics: `(x, y)` is the top-left corner
- 🟢 28 tests

### Known, not fixed

- `Type.hpp` is an umbrella header that pulls everything in — `igraphic`
  only ever includes it, eight times, and pays for `Vector4`, `Matrix`
  and `Quaternion` it never uses
- declared `STATIC` with no sources: produces an empty `.a`, should be
  `INTERFACE`
