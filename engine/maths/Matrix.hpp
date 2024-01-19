#ifndef MATRIX_HPP
#define MATRIX_HPP  

#include "platforms/macros_platform.h"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Maths.hpp"

#include <memory>

#define MATRIX_TEMPLATE template<const unsigned short X, const unsigned short Y, typename T, typename ALLOC>

template <const unsigned short X, const unsigned short Y, typename T = float, typename ALLOC = std::allocator<T>>
class Matrix final
{
public:
        // CONSTRUCTEURS

    Matrix();
    Matrix(const T identityValue);
    ~Matrix() noexcept;

        // METHODES

        // Libère la mémoire allouée
    void Destroy()  noexcept;
        // Libère la mémoire allouée et supprime l'objet
    void Free()     noexcept;

    inline void Scale2D(const Vector2<T>& vec2)     noexcept;
    inline void Scale   (const Vector3<T>& vec3)    noexcept;

    inline void Translation2D(const Vector2<T>& vec2)   noexcept;
    inline void Translation (const Vector3<T>& vec3)    noexcept;

    inline void Rotation    (const Vector3<T>&   vec3, const float& angle)  noexcept;
    inline void Rotation2D  (const Vector2<T>& vec2)                        noexcept;

    inline void Transformation   (const Vector3<T>& pos,
                                  const Vector3<T>& scale,
                                  const Vector3<T>& rot)      noexcept;
    inline void Transformation2D (const Vector2<T>& pos,
                                  const Vector2<T>& scale,
                                  const Vector2<T>& rot)      noexcept;

    void LookAt (const Vector3<T>& camera_position,
                        const Vector3<T>& camera_target,
                        const Vector3<T>& up)    noexcept;
    void Perspective (const float& FOV, const float& width, 
                             const float& height, const float& zNear, 
                             const float& zFar)  noexcept;

    inline void Debug() const;
    inline T& at(const uint16&& x, const uint16&& y)    const   noexcept    FREQ
    { return this->datas[x * Y + y]; }
    inline T*   Ref  () const noexcept;

        // STATIQUES

        // OPERATEURS

    inline const Matrix<X, Y, T, ALLOC> operator*(const Matrix<X, Y, T, ALLOC>& mat)    const   noexcept
    {
        for (uint32 i = 0; i < X; i++)
            for (uint32 j = 0; j < Y; j++)
                for (uint32 k = 0; k < Y; k++)
                    this->at(i, j) += this->at(i, k) * mat.at(k, j);
        return (*this);
    }

public:
        // VARIABLES

    T*      datas;

private:

    ALLOC   localalloc;
};

    // INT matrix

typedef Matrix<3U, 3U, int, std::allocator<int>>                    Matrix3x3i;
typedef Matrix<4U, 3U, int, std::allocator<int>>                    Matrix4x3i;
typedef Matrix<3U, 4U, int, std::allocator<int>>                    Matrix3x4i;
typedef Matrix<4U, 4U, int, std::allocator<int>>                    Matrix4x4i;
typedef Matrix<3U, 3U, int, std::allocator<int>>                    Matrix3i;
typedef Matrix<4U, 4U, int, std::allocator<int>>                    Matrix4i;

    // FLOAT matrix

typedef Matrix<3U, 3U, float, std::allocator<float>>                Matrix3x3f;
typedef Matrix<4U, 3U, float, std::allocator<float>>                Matrix4x3f;
typedef Matrix<3U, 4U, float, std::allocator<float>>                Matrix3x4f;
typedef Matrix<4U, 4U, float, std::allocator<float>>                Matrix4x4f;
typedef Matrix<3U, 3U, float, std::allocator<float>>                Matrix3f;
typedef Matrix<4U, 4U, float, std::allocator<float>>                Matrix4f;

typedef Matrix<3U, 3U, float, std::allocator<float>>                Matrix3x3;
typedef Matrix<4U, 3U, float, std::allocator<float>>                Matrix4x3;
typedef Matrix<3U, 4U, float, std::allocator<float>>                Matrix3x4;
typedef Matrix<4U, 4U, float, std::allocator<float>>                Matrix4x4;
typedef Matrix<3U, 3U, float, std::allocator<float>>                Matrix3;
typedef Matrix<4U, 4U, float, std::allocator<float>>                Matrix4;

    // DOUBLE matrix

typedef Matrix<3U, 3U, double, std::allocator<double>>              Matrix3x3d;
typedef Matrix<4U, 3U, double, std::allocator<double>>              Matrix4x3d;
typedef Matrix<3U, 4U, double, std::allocator<double>>              Matrix3x4d;
typedef Matrix<4U, 4U, double, std::allocator<double>>              Matrix4x4d;
typedef Matrix<3U, 3U, double, std::allocator<double>>              Matrix3d;
typedef Matrix<4U, 4U, double, std::allocator<double>>              Matrix4d;

    // LONG DOUBLE matrix

typedef Matrix<3U, 3U, long double, std::allocator<long double>>    Matrix3x3ld;
typedef Matrix<4U, 3U, long double, std::allocator<long double>>    Matrix4x3ld;
typedef Matrix<3U, 4U, long double, std::allocator<long double>>    Matrix3x4ld;
typedef Matrix<4U, 4U, long double, std::allocator<long double>>    Matrix4x4ld;
typedef Matrix<3U, 3U, long double, std::allocator<long double>>    Matrix3ld;
typedef Matrix<4U, 4U, long double, std::allocator<long double>>    Matrix4ld;

#include "src/Matrix.inl"

#endif