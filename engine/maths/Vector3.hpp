#ifndef  VECTOR3_HPP
#define  VECTOR3_HPP

#include <cmath>

#define BOOL unsigned short

template <typename T = float>
class Vector3 final
{
public:
    
        //  CONSTRUCTEURS
    Vector3 (const T&& x,   const T&& y,   const T&& z)   noexcept;
    Vector3 (const T&& x, const T&& y)                    noexcept;
    Vector3 (const T& x, const T& y, const T& z)          noexcept;
    Vector3 (const T& x, const T& y)                      noexcept;
    Vector3 (const T&& identity)                          noexcept;
    Vector3 (const T& identity)                           noexcept;
    Vector3 (const Vector3<T>& copy)                      noexcept;
    Vector3 ()                                            noexcept;
    ~Vector3()                                            noexcept;

        //  METHODES

    inline const Vector3<T> Scalar(const Vector3<T>& otherCpy, const float angle = 90.f) const noexcept;
    inline const Vector3<T> Cross (const Vector3<T>& otherCpy)                           const noexcept;
    inline const T Dot(const Vector3<T>& otherCpy)                                       const noexcept;
    inline Vector3<T> Magnitude()                                                        const noexcept;
    inline const T Norm()                                                                const noexcept;
    inline const BOOL NotNull()                                                          const noexcept;
    inline const Vector3<T> Oppose (const Vector3<T>& otherCpy)                          const noexcept;

    constexpr void Debug() const noexcept 
    { printf("x : %f, y : %f, z : %f", this->x, this->y, this->z); }

        //  STATIQUES

    inline static const Vector3<T> Scalar(const Vector3<T>& aCpy, const Vector3<T>& bCpy, const float angle = 90.f)  noexcept;
    inline static const Vector3<T> Cross (const Vector3<T>& aCpy, const Vector3<T>& bCpy)                            noexcept;
    inline static const T Dot(const Vector3<T>& aCpy, const Vector3<T>& bCpy)                                        noexcept;
    inline static const Vector3<T> Magnitude(const Vector3<T>& acpy)                                                 noexcept;
    inline static const T Norm(const Vector3<T>& aCpy)                                                               noexcept;
    inline static const Vector3<T> Oppose (const Vector3<T>& aCpy, const Vector3<T>& bCpy)                           noexcept;

        //  OPERATORS

    inline const BOOL operator==(const Vector3<T>& aCpy)    const noexcept;
    inline const BOOL operator==(const T&&      x)          const noexcept;
    inline const BOOL operator==(const T&       x)          const noexcept;
    inline const BOOL operator!=(const Vector3<T>& aCpy)    const noexcept;
    inline const BOOL operator!=(const T&& x)               const noexcept;
    inline const BOOL operator!=(const T&  x)               const noexcept;

    inline const Vector3<T> operator+(const Vector3<T>& aCpy)  const noexcept;
    inline const Vector3<T> operator+(const T&& x)             const noexcept;
    inline const Vector3<T> operator+(const T&  x)             const noexcept;
    inline const void       operator+=(const Vector3<T>& aCpy)       noexcept;
    inline const void       operator+=(const T&& x)                  noexcept;
    inline const void       operator+=(const T&  x)                  noexcept;

    inline const Vector3<T> operator-(const Vector3<T>& aCpy)  const noexcept;
    inline const Vector3<T> operator-(const T&& x)             const noexcept;
    inline const Vector3<T> operator-(const T&  x)             const noexcept;
    inline const void       operator-=(const Vector3<T>& aCpy)       noexcept;
    inline const void       operator-=(const T&& x)                  noexcept;
    inline const void       operator-=(const T&  x)                  noexcept;

    inline const Vector3<T> operator*(const Vector3<T>& aCpy)  const noexcept;
    inline const Vector3<T> operator*(const T&& x)             const noexcept;
    inline const Vector3<T> operator*(const T&  x)             const noexcept;
    inline const void       operator*=(const Vector3<T>& aCpy)       noexcept;
    inline const void       operator*=(const T&& x)                  noexcept;
    inline const void       operator*=(const T&  x)                  noexcept;

    inline const Vector3<T> operator/(const Vector3<T>& aCpy)  const noexcept;
    inline const Vector3<T> operator/(const T&& x)             const noexcept;
    inline const Vector3<T> operator/(const T&  x)             const noexcept;
    inline const void       operator/=(const Vector3<T>& aCpy)       noexcept;
    inline const void       operator/=(const T&& x)                  noexcept;
    inline const void       operator/=(const T&  x)                  noexcept;

    inline void operator=(const Vector3<T>& aCpy)  noexcept;

        //  VARIABLES
    T x, y, z;

    inline static const Vector3<T> right   = Vector3<T>(1.0f, 0.0f, 0.0f);
    inline static const Vector3<T> up      = Vector3<T>(0.0f, 1.0f, 0.0f);
    inline static const Vector3<T> forward = Vector3<T>(0.0f, 0.0f, 1.0f);

private:
        //  METHODES
    inline void _Set(const T x = static_cast<T>(0), const T y = static_cast<T>(0), const T z = static_cast<T>(0)) noexcept;
};

typedef  Vector3<unsigned char>   Vector3uc;
typedef  Vector3<char>            Vector3c ;
typedef  Vector3<unsigned int>    Vector3ui;
typedef  Vector3<int>             Vector3i ;
typedef  Vector3<float>           Vector3f ;
typedef  Vector3<double>          Vector3d ;

#include "src/Vector3.inl"

#endif