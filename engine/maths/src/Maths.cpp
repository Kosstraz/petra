#include "../Maths.hpp"

    /*////////////*/
    /// deg_rad  ///
    /*////////////*/

float Maths::deg_to_rad(const float& deg) noexcept
{   return ((deg * PI) / 180.f);  }

float Maths::rad_to_deg(const float& rad) noexcept
{   return ((rad * 180.f) / PI);    }

    /*////////////*/
    /// lerping  ///
    /*////////////*/

float Maths::lerp(const float& a, const float& b, const float& t) noexcept
{   return (lerp_precise(a, b, t));    }

float Maths::lerp_precise(const float& a, const float& b, const float& t) noexcept
{   return ((1 - t) * a + t * b);   }

float Maths::lerp_imprecise(const float& a, const float& b, const float& t) noexcept
{   return (a + t * (b - a));   }