#include "../Maths.hpp"

float Maths::deg_to_rad(const float& deg) noexcept
{   return ((deg * PI) / 180.f);  }

float Maths::rad_to_deg(const float& rad) noexcept
{   return ((rad * 180.f) / PI);    }