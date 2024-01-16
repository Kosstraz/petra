#include "../Vector2.hpp"

///////////////
/*  PUBLIC  */
///////////////

    // CONSTRUCTEURS

template <typename T>
Vector2<T>::Vector2(const T&& x, const T&& y) noexcept
{  
    this->x = static_cast<T>(x);
    this->y = static_cast<T>(y);
}

template <typename T>
Vector2<T>::Vector2(const T&& x) noexcept
{  
    this->x = static_cast<T>(x);
    this->y = static_cast<T>(y);
}

template <typename T>
Vector2<T>::Vector2(const T& x, const T& y) noexcept
{
    this->x = x;
    this->y = y;
}

template <typename T>
Vector2<T>::Vector2(const T& x) noexcept
{
    this->x = x;
    this->y = y;
}

template <typename T>
Vector2<T>::Vector2(const Vector2<T>& copy) noexcept
{  *this = copy;        }

template <typename T>
Vector2<T>::Vector2() noexcept
{
    this->x = static_cast<T>(0);
    this->y = static_cast<T>(0);
}

template <typename T>
Vector2<T>::~Vector2() noexcept
{  this->_Set();      }

    //  METHODES

template <typename T>
inline const Vector2<T> Vector2<T>::Scalar(const Vector2<T>& otherCpy, float angle) const noexcept
{
    return ( this->Norm() * otherCpy.Norm() * static_cast<T>(sinf(angle)) );
}

template <typename T>
inline const BOOL Vector2<T>::NotNull() const noexcept
{
    if (*this == static_cast<T>(0))   return (0x00);    // false
    return (0x01);                                      // true
}

template <typename T>
inline const T Vector2<T>::Dot(const Vector2<T>& otherCpy) const noexcept
{
    return (this->x * otherCpy.x   +   this->y * otherCpy.y);
}

template <typename T>
inline const T Vector2<T>::Norm() const noexcept
{
    return static_cast<T>( sqrtf((this->x * this->x)   +   (this->y * this->y)) );
}

    //  STATIQUES

template <typename T>
inline const Vector2<T> Vector2<T>::Scalar(const Vector2<T>& aCpy, const Vector2<T>& bCpy, float angle) noexcept
{
    return ( aCpy.Norm() * bCpy.Norm() * static_cast<T>(sinf(angle)) );
}

template <typename T>
inline const T Vector2<T>::Dot(const Vector2<T>& aCpy, const Vector2<T>& bCpy) noexcept
{
    return (aCpy.x * bCpy.x    +   aCpy.y * bCpy.y);
}

template <typename T>
inline const T Vector2<T>::Norm(const Vector2<T>& otherCpy) noexcept
{
    return static_cast<T>( sqrtf((otherCpy.x * otherCpy.x)   +   (otherCpy.y * otherCpy.y)) );
}


    // OPERATORS

template <typename T>
inline const BOOL Vector2<T>::operator==(const Vector2<T>& aCpy) const noexcept
{
    if (this->x == aCpy.x && this->y == aCpy.y)   return (0x01);    // true
    return (0x00);                                                  // false
}

template <typename T>
inline const BOOL Vector2<T>::operator==(const T&& x) const noexcept
{
    if (this->x == x && this->y == x)   return(0x01);  // true
    return (0x00);                                     // false
}

template <typename T>
inline const BOOL Vector2<T>::operator==(const T& x) const noexcept
{
    if (this->x == x && this->y == x)   return (0x01);  // true
    return (0x00);                                      // false
}

template <typename T>
inline const BOOL Vector2<T>::operator!=(const Vector2<T>& aCpy) const noexcept
{
    if (*this == aCpy)   return (0x00); // false
    return (0x01);                      // true
}

template <typename T>
inline const BOOL Vector2<T>::operator!=(const T&& x) const noexcept
{
    if (*this == x)   return (0x00);    // false
    return (0x01);                      // true
}

template <typename T>
inline const BOOL Vector2<T>::operator!=(const T& x) const noexcept
{
    if (*this == x)   return (0x00);    // false
    return  (0x01);                     // true
}



template <typename T>
inline const Vector2<T> Vector2<T>::operator+(const Vector2<T>& aCpy) const noexcept
{   return (Vector2<T>(this.x + aCpy.x,  this.y + aCpy.y)); }

template <typename T>
inline const Vector2<T> Vector2<T>::operator+(const T&& x) const noexcept
{   return (Vector2<T>(this.x + x,  this.y + x)); }

template <typename T>
inline const Vector2<T> Vector2<T>::operator+(const T& x) const noexcept
{   return (Vector2<T>(this.x + x,  this.y + x)); }

template <typename T>
inline const void Vector2<T>::operator+=(const Vector2<T>& aCpy) noexcept
{   this->x += aCpy.x;  this->y += aCpy.y; }

template <typename T>
inline const void Vector2<T>::operator+=(const T&& x) noexcept
{   this->x += x;  this->y += x; }

template <typename T>
inline const void Vector2<T>::operator+=(const T& x) noexcept
{   this->x += x;  this->y += x; }



template <typename T>
inline const Vector2<T> Vector2<T>::operator-(const Vector2<T>& aCpy) const noexcept
{   return (Vector2<T>(this.x - aCpy.x,  this.y - aCpy.y)); }

template <typename T>
inline const Vector2<T> Vector2<T>::operator-(const T&& x) const noexcept
{   return (Vector2<T>(this.x - x,  this.y - x)); }

template <typename T>
inline const Vector2<T> Vector2<T>::operator-(const T& x) const noexcept
{   return (Vector2<T>(this.x - x,  this.y - x)); }

template <typename T>
inline const void Vector2<T>::operator-=(const Vector2<T>& aCpy) noexcept
{   this->x -= aCpy.x;  this->y -= aCpy.y; }

template <typename T>
inline const void Vector2<T>::operator-=(const T&& x) noexcept
{   this->x -= x;  this->y -= x; }

template <typename T>
inline const void Vector2<T>::operator-=(const T& x) noexcept
{   this->x -= x;  this->y -= x; }



template <typename T>
inline const Vector2<T> Vector2<T>::operator*(const Vector2<T>& aCpy) const noexcept
{   return (Vector2<T>(this.x * aCpy.x,  this.y * aCpy.y)); }

template <typename T>
inline const Vector2<T> Vector2<T>::operator*(const T&& x) const noexcept
{   return (Vector2<T>(this.x * x,  this.y * x)); }

template <typename T>
inline const Vector2<T> Vector2<T>::operator*(const T& x) const noexcept
{   return (Vector2<T>(this.x * x,  this.y * x)); }

template <typename T>
inline const void Vector2<T>::operator*=(const Vector2<T>& aCpy) noexcept
{   this->x *= aCpy.x;  this->y *= aCpy.y; }

template <typename T>
inline const void Vector2<T>::operator*=(const T&& x) noexcept
{   this->x *= x;  this->y *= x; }

template <typename T>
inline const void Vector2<T>::operator*=(const T& x) noexcept
{   this->x *= x;  this->y *= x; }



template <typename T>
inline const Vector2<T> Vector2<T>::operator/(const Vector2<T>& aCpy) const noexcept
{   return (Vector2<T>(this.x / aCpy.x,  this.y / aCpy.y)); }

template <typename T>
inline const Vector2<T> Vector2<T>::operator/(const T&& x) const noexcept
{   return (Vector2<T>(this.x / x,  this.y / x)); }

template <typename T>
inline const Vector2<T> Vector2<T>::operator/(const T& x) const noexcept
{   return (Vector2<T>(this.x / x,  this.y / x)); }

template <typename T>
inline const void Vector2<T>::operator/=(const Vector2<T>& aCpy) noexcept
{   this->x /= aCpy.x;  this->y /= aCpy.y; }

template <typename T>
inline const void Vector2<T>::operator/=(const T&& x) noexcept
{   this->x /= x;  this->y /= x; }

template <typename T>
inline const void Vector2<T>::operator/=(const T& x) noexcept
{   this->x /= x;  this->y /= x; }

///////////////
/*  PRIVATE  */
///////////////

template <typename T>
inline void Vector2<T>::_Set(const T x, const T y) noexcept
{
    this->x = x;
    this->y = y;
}