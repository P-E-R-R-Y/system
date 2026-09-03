# system — journal

Marqueurs : 🟢 ajout · 🔴 rupture · 🔵 correctif · ⚪ interne ou doc · 🟡 propose
dans le plan, code non ecrit.

## v1.0.0

- 🟢 `Vector2/3/4`, `Matrix`, `Quaternion`, `Color`, `Constants`, `Lambdify`
- 🟢 `Rect` a semantique **coin** : `(x, y)` est le coin haut-gauche
- 🟢 28 tests

### Constate, pas corrige

- `Type.hpp` est un en-tete parapluie qui tire tout : `igraphic` n'inclut
  que lui, huit fois, et paie `Vector4`, `Matrix` et `Quaternion` sans
  s'en servir
- declare `STATIC` sans aucune source : produit un `.a` vide, devrait
  etre `INTERFACE`
