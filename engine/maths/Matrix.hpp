#ifndef MATRIX_HPP
#define MATRIX_HPP  

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Maths.hpp"

#define MATRIX_TEMPLATE template<const unsigned short X, const unsigned short Y, typename T>

template <const unsigned short X, const unsigned short Y, typename T = float>
class Matrix final
{
public:
    // CONSTRUCTEURS
    Matrix();
    Matrix(const T identityValue);
    ~Matrix() noexcept;

    // METHODES

    void Free() noexcept;

    inline void Scale2D(const Vector2<T>& vec2)  noexcept;
    inline void Scale(const Vector3<T>& vec3)    noexcept;

    inline void Translation2D(const Vector2<T>& vec2)  noexcept;
    inline void Translation(const Vector3<T>& vec3)    noexcept;

    inline void Rotation(const Vector3<T>&   vec3)  noexcept;
    inline void Rotation2D(const Vector2<T>& vec2)  noexcept;

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
    inline T& at(const uint16 x, const uint16 y) const noexcept
    { return this->datas[x * Y + y]; }
    inline T*   Ref  () const noexcept;

    // STATIQUES

    // OPERATEURS

public:
    // VARIABLES

    T* datas;
};

typedef Matrix<3U, 3U, int> Matrix3x3i;
typedef Matrix<4U, 3U, int> Matrix4x3i;
typedef Matrix<3U, 4U, int> Matrix3x4i;
typedef Matrix<4U, 4U, int> Matrix4x4i;

typedef Matrix<3U, 3U, float> Matrix3x3f;
typedef Matrix<4U, 3U, float> Matrix4x3f;
typedef Matrix<3U, 4U, float> Matrix3x4f;
typedef Matrix<4U, 4U, float> Matrix4x4f;

typedef Matrix<3U, 3U, float> Matrix3x3;
typedef Matrix<4U, 3U, float> Matrix4x3;
typedef Matrix<3U, 4U, float> Matrix3x4;
typedef Matrix<4U, 4U, float> Matrix4x4;

typedef Matrix<3U, 3U, double> Matrix3x3d;
typedef Matrix<4U, 3U, double> Matrix4x3d;
typedef Matrix<3U, 4U, double> Matrix3x4d;
typedef Matrix<4U, 4U, double> Matrix4x4d;

typedef Matrix<3U, 3U, long double> Matrix3x3ld;
typedef Matrix<4U, 3U, long double> Matrix4x3ld;
typedef Matrix<3U, 4U, long double> Matrix3x4ld;
typedef Matrix<4U, 4U, long double> Matrix4x4ld;

#include "src/Matrix.inl"

#endif