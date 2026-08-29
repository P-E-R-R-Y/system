# system

> The vocabulary types everything else shares.

Header-only, no dependency. Whatever two libraries need to agree on before
they can talk to each other.

- `Vector2.hpp` / `Vector3.hpp` / `Vector4.hpp`, `Matrix.hpp`, `Quaternion.hpp`
- `Color.hpp`, `Shape.hpp` — `Line<T>`, `Triangle<T>`
- `Type.hpp` — `OS`, and the aliases used across the engine
- `Constants.hpp`, `Lambdify.hpp`, `std.hpp`
