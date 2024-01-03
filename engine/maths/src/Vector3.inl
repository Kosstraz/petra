#include "../Vector3.hpp"

///////////////
/*  PUBLIC  */
///////////////

    // CONSTRUCTEURS

/**/template <typename T>
Vector3<T>::Vector3(const T&& x, const T&& y, const T&& z) noexcept
{  
    this->x = static_cast<T>(x);
    this->y = static_cast<T>(y);
    this->z = static_cast<T>(z);
}

template <typename T>
Vector3<T>::Vector3(const T&& x, const T&& y) noexcept
{  
    this->x = static_cast<T>(x);
    this->y = static_cast<T>(y);
}

template <typename T>
Vector3<T>::Vector3(const T& x, const T& y, const T& z) noexcept
{
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename T>
Vector3<T>::Vector3(const T& x, const T& y) noexcept
{
    this->x = x;
    this->y = y;    
}

template <typename T>
Vector3<T>::Vector3(const T&& identity) noexcept
{
    this->x = identity;
    this->y = identity;   
    this->z = identity; 
}

template <typename T>
Vector3<T>::Vector3(const T& identity) noexcept
{
    this->x = identity;
    this->y = identity;   
    this->z = identity; 
}

template <typename T>
Vector3<T>::Vector3(const Vector3<T>& copy) noexcept
{  *this = copy;        }

template <typename T>
Vector3<T>::Vector3() noexcept
{}

template <typename T>
Vector3<T>::~Vector3() noexcept
{  this->_Set();      }

    //  METHODES

template <typename T>
inline const Vector3<T> Vector3<T>::Scalar(const Vector3<T>& otherCpy, const float angle) const noexcept
{
    return ( this->Norm() * otherCpy.Norm() * static_cast<T>(sinf(angle)) );
}

template <typename T>
inline const T Vector3<T>::Dot(const Vector3<T>& otherCpy) const noexcept    /// A modifier
{
    return (this->x * otherCpy.x   +   this->y * otherCpy.y);
}

template <typename T>
inline Vector3<T> Vector3<T>::Magnitude() const noexcept
{
    T norm = Vector3<T>::Norm(*this);
    return  (Vector3<T>(this->x / norm, this->y / norm, this->z / norm));
}

template <typename T>
inline const T Vector3<T>::Norm() const noexcept
{
    return  static_cast<T>( sqrtf((this->x * this->x)   +   (this->y * this->y)     +   (this->z * this->z)) );
}

template <typename T>
inline const BOOL Vector3<T>::NotNull() const noexcept
{
    if(this == 0)   return false;
    return true;
}

    //  STATIQUES

template <typename T>
inline const Vector3<T> Vector3<T>::Scalar(const Vector3<T>& aCpy, const Vector3<T>& bCpy, const float angle) noexcept
{
    return ( aCpy.Magnitude() * bCpy.Magnitude() * static_cast<T>(sinf(angle)) );
}

template <typename T>
inline const T Vector3<T>::Dot(const Vector3<T>& aCpy, const Vector3<T>& bCpy) noexcept /// A modifier
{
    return aCpy.Dot(bCpy);
}

template <typename T>
inline const  Vector3<T> Vector3<T>::Magnitude(const Vector3<T>& aCpy) noexcept /// A modifier
{
    return aCpy.Magnitude();
}   

template <typename T>
inline const T Vector3<T>::Norm(const Vector3<T>& otherCpy) noexcept
{
    return  static_cast<T>( sqrtf((otherCpy.x * otherCpy.x)   +   (otherCpy.y * otherCpy.y)     +   (otherCpy.z * otherCpy.z)) );
}


    // OPERATORS

template <typename T>
inline const BOOL Vector3<T>::operator==(const Vector3<T>& aCpy) const noexcept
{
    if (this->x == aCpy.x && this->y == aCpy.y && this->z == aCpy.z)   return true;
    return false;
}

template <typename T>
inline const BOOL Vector3<T>::operator==(const T&& x) const noexcept
{
    if (this->x == x && this->y == x && this->z == x)   return true;
    return false;
}

template <typename T>
inline const BOOL Vector3<T>::operator==(const T& x) const noexcept
{
    if (this->x == x && this->y == x && this->z == x)   return true;
    return false;
}

template <typename T>
inline const BOOL Vector3<T>::operator!=(const Vector3<T>& aCpy) const noexcept
{
    if (*this == aCpy)   return false;
    return true;
}

template <typename T>
inline const BOOL Vector3<T>::operator!=(const T&& x) const noexcept
{
    if (*this == x)   return false;
    return true;
}

template <typename T>
inline const BOOL Vector3<T>::operator!=(const T& x) const noexcept
{
    if (*this == x)   return false;
    return true;
}



template <typename T>
inline const Vector3<T> Vector3<T>::operator+(const Vector3<T>& aCpy) const noexcept
{   return (Vector3<T>(this->x + aCpy.x,  this->y + aCpy.y, this->z + aCpy.z)); }

template <typename T>
inline const Vector3<T> Vector3<T>::operator+(const T&& x) const noexcept
{   return (Vector3<T>(this->x + x,  this->y + x, this->z + x.z)); }

template <typename T>
inline const Vector3<T> Vector3<T>::operator+(const T& x) const noexcept
{   return (Vector3<T>(this->x + x,  this->y + x, this->z + x.z)); }

template <typename T>
inline const void Vector3<T>::operator+=(const Vector3<T>& aCpy) noexcept
{   this->x += aCpy.x;  this->y += aCpy.y;  this->z += aCpy.z; }

template <typename T>
inline const void Vector3<T>::operator+=(const T&& x) noexcept
{   this->x += x;  this->y += x;  this->z += x; }

template <typename T>
inline const void Vector3<T>::operator+=(const T& x) noexcept
{   this->x += x;  this->y += x;  this->z += x; }



template <typename T>
inline const Vector3<T> Vector3<T>::operator-(const Vector3<T>& aCpy) const noexcept
{   return (Vector3<T>(this->x - aCpy.x,  this->y - aCpy.y, this->z - aCpy.z)); }

template <typename T>
inline const Vector3<T> Vector3<T>::operator-(const T&& x) const noexcept
{   return (Vector3<T>(this->x - x,  this->y - x,  this->z - x)); }

template <typename T>
inline const Vector3<T> Vector3<T>::operator-(const T& x) const noexcept
{   return (Vector3<T>(this->x - x,  this->y - x,  this->z - x)); }

template <typename T>
inline const void Vector3<T>::operator-=(const Vector3<T>& aCpy) noexcept
{   this->x -= aCpy.x;  this->y -= aCpy.y;  this->z -= aCpy.z; }

template <typename T>
inline const void Vector3<T>::operator-=(const T&& x) noexcept
{   this->x -= x;  this->y -= x;    this->z -= x; }

template <typename T>
inline const void Vector3<T>::operator-=(const T& x) noexcept
{   this->x -= x;  this->y -= x;    this->z -= x; }



template <typename T>
inline const Vector3<T> Vector3<T>::operator*(const Vector3<T>& aCpy) const noexcept
{   return (Vector3<T>(this->x * aCpy.x,  this->y * aCpy.y,  this->z * aCpy.z)); }

template <typename T>
inline const Vector3<T> Vector3<T>::operator*(const T&& x) const noexcept
{   return (Vector3<T>(this->x * x,  this->y * x,  this->z * x)); }

template <typename T>
inline const Vector3<T> Vector3<T>::operator*(const T& x) const noexcept
{   return (Vector3<T>(this->x * x,  this->y * x,  this->z * x)); }

template <typename T>
inline const void Vector3<T>::operator*=(const Vector3<T>& aCpy) noexcept
{   this->x *= aCpy.x;  this->y *= aCpy.y;  this->z *= aCpy.z; }

template <typename T>
inline const void Vector3<T>::operator*=(const T&& x) noexcept
{   this->x *= x;  this->y *= x;    this->z *= x; }

template <typename T>
inline const void Vector3<T>::operator*=(const T& x) noexcept
{   this->x *= x;  this->y *= x;    this->z *= x; }



template <typename T>
inline const Vector3<T> Vector3<T>::operator/(const Vector3<T>& aCpy) const noexcept
{   return (Vector3<T>(this->x / aCpy.x,  this->y / aCpy.y,  this->z / aCpy.z)); }

template <typename T>
inline const Vector3<T> Vector3<T>::operator/(const T&& x) const noexcept
{   return (Vector3<T>(this->x / x,  this->y / x,  this->z / x)); }

template <typename T>
inline const Vector3<T> Vector3<T>::operator/(const T& x) const noexcept
{   return (Vector3<T>(this->x / x,  this->y / x,  this->z / x)); }

template <typename T>
inline const void Vector3<T>::operator/=(const Vector3<T>& aCpy) noexcept
{   this->x /= aCpy.x;  this->y /= aCpy.y;  this->y /= aCpy.z; }

template <typename T>
inline const void Vector3<T>::operator/=(const T&& x) noexcept
{   this->x /= x;  this->y /= x;    this->z /= x; }

template <typename T>
inline const void Vector3<T>::operator/=(const T& x) noexcept
{   this->x /= x;  this->y /= x;    this->z /= x; }

template <typename T>
inline void Vector3<T>::operator=(const Vector3<T>& cpy) noexcept
{   this->x = cpy.x;  this->y = cpy.y;    this->z = cpy.z; }

///////////////
/*  PRIVATE  */
///////////////

template <typename T>
inline void Vector3<T>::_Set(const T x, const T y, const T z) noexcept
{
    this->x = x;
    this->y = y;
    this->z = z;
}