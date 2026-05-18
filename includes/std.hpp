/**
 * @file std.hpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief 
 * @date 2026-05-18
 */

#pragma once

#include <ostream>

namespace std {  // Open the std namespace (this is generally discouraged)
    // Define the manipulator inside the std namespace
    inline std::ostream& tab(std::ostream& os) {
        return os << '\t';
    }
}
