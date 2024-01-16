#ifndef  VECTOR2_HPP
#define  VECTOR2_HPP

#include <cmath>

#define BOOL unsigned short

template <typename T = float>
class Vector2 final
{
public:
    
        //  CONSTRUCTEURS
    Vector2 (const T&& x, const T&& y) noexcept;
    Vector2 (const T&& x)              noexcept;
    Vector2 (const T& x, const T& y)   noexcept;
    Vector2 (const T& x)               noexcept;
    Vector2 (const Vector2& copy)      noexcept;
    Vector2 ()                         noexcept;
    ~Vector2()                         noexcept;

        //  METHODES

    inline const Vector2 Scalar(const Vector2& otherCpy, float angle) const noexcept;
    inline const T Dot(const Vector2& otherCpy)                 const noexcept;
    inline const BOOL NotNull()                                 const noexcept;
    inline const T Norm()                                       const noexcept;

        //  STATIQUES

    inline static const Vector2 Scalar(const Vector2& aCpy, const Vector2& bCpy, float angle)  noexcept;
    inline static const T Dot(const Vector2& aCpy, const Vector2& bCpy)                  noexcept;
    inline static const T Norm(const Vector2& aCpy)                                      noexcept;

        //  OPERATORS

    inline Vector2& operator=(const Vector2& cpyRef)            noexcept
    {
        if (this != &cpyRef)
        {
            this->x = cpyRef.x;
            this->y = cpyRef.y;
        }
        return *this;
    }

    inline const BOOL operator==(const Vector2& cpy)    const noexcept;
    inline const BOOL operator==(const T&&      x)       const noexcept;
    inline const BOOL operator==(const T&       x)       const noexcept;
    inline const BOOL operator!=(const Vector2& cpy)    const noexcept;
    inline const BOOL operator!=(const T&& x)            const noexcept;
    inline const BOOL operator!=(const T&  x)            const noexcept;

    inline const Vector2 operator+(const Vector2& cpy)  const noexcept;
    inline const Vector2 operator+(const T&& x)       const noexcept;
    inline const Vector2 operator+(const T&  x)       const noexcept;
    inline const void    operator+=(const Vector2& cpy)       noexcept;
    inline const void    operator+=(const T&& x)            noexcept;
    inline const void    operator+=(const T&  x)            noexcept;

    inline const Vector2 operator-(const Vector2& cpy)  const noexcept;
    inline const Vector2 operator-(const T&& x)       const noexcept;
    inline const Vector2 operator-(const T&  x)       const noexcept;
    inline const void    operator-=(const Vector2& cpy)       noexcept;
    inline const void    operator-=(const T&& x)            noexcept;
    inline const void    operator-=(const T&  x)            noexcept;

    inline const Vector2 operator*(const Vector2& cpy)  const noexcept;
    inline const Vector2 operator*(const T&& x)       const noexcept;
    inline const Vector2 operator*(const T&  x)       const noexcept;
    inline const void    operator*=(const Vector2& cpy)       noexcept;
    inline const void    operator*=(const T&& x)            noexcept;
    inline const void    operator*=(const T&  x)            noexcept;

    inline const Vector2 operator/(const Vector2& cpy)  const noexcept;
    inline const Vector2 operator/(const T&& x)       const noexcept;
    inline const Vector2 operator/(const T&  x)       const noexcept;
    inline const void    operator/=(const Vector2& aCpy)       noexcept;
    inline const void    operator/=(const T&& x)            noexcept;
    inline const void    operator/=(const T&  x)            noexcept;

        //  VARIABLES
    T x, y;

private:
        //  METHODES
    inline void _Set(const T x = static_cast<T>(0), const T y = static_cast<T>(0)) noexcept;
};

typedef  Vector2<unsigned char>   Vector2uc;
typedef  Vector2<char>            Vector2c ;
typedef  Vector2<unsigned int>    Vector2ui;
typedef  Vector2<int>             Vector2i ;
typedef  Vector2<float>           Vector2f ;
typedef  Vector2<double>          Vector2d ;

#include "src/Vector2.inl"

#endif