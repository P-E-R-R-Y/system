// Lambdify.hpp
/**
 * @file Lambdify.hpp
 * @author Perry Chouteau
 * @date 2025-11-05
 * @brief A simple utility to wrap stateless functions into callable objects.
 */

//todo could be great to add a c++11 version ("template<auto Func>" is forcing minimum c++17) 

#pragma once

#include <utility>
#include <type_traits>

// wrapper stateless générique
template<auto Func>
struct lambdify {
    // type par défaut
    struct type {
        constexpr type() = default; // default-constructible

        // opérateur () qui forward les arguments vers la fonction réelle
        template<typename... Args>
        constexpr auto operator()(Args&&... args) const 
            -> decltype(Func(std::forward<Args>(args)...))
        {
            return Func(std::forward<Args>(args)...);
        }
    };
};

// Helper alias
template<auto Func>
using lambdify_t = typename lambdify<Func>::type;
