#ifndef MATHS_HPP
#define MATHS_HPP

#include <cmath>

#include "platforms/types_macros.hpp"

#define PI (double)3.14159265358979323846264338327950288419716939937510582

namespace Maths
{
    float deg_to_rad(const float& deg) noexcept;

    float rad_to_deg(const float& rad) noexcept;

        // Equivalent à la fonction 'lerp_precise( ... )'
    float lerp(const float& a, const float& b, const float& t) noexcept;

    float lerp_precise(const float& a, const float& b, const float& t) noexcept;
    
    float lerp_imprecise(const float& a, const float& b, const float& t) noexcept;

    int  abs_ui(int val)  noexcept;
};

#endif