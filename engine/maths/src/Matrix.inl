#include "../Matrix.hpp"

    // CONSTRUCTEURS

MATRIX_TEMPLATE
Matrix<X, Y, T, ALLOC>::Matrix()
{
    this->datas = localalloc.allocate(X * Y);
    for (uint8 x = 0; x < X; x++)
    {
        for (uint8 y = 0; y < Y; y++)
            localalloc.construct(this->datas + (x * Y + y), static_cast<T>(0));
    }
}

MATRIX_TEMPLATE
Matrix<X, Y, T, ALLOC>::Matrix(const T identityValue)
{
    this->datas = localalloc.allocate(X * Y);
    for (uint8 x = 0; x < X; x++)
    {
        for (uint8 y = 0; y < Y; y++)
        {
            if (x == y)
                localalloc.construct(this->datas + (x * Y + y), identityValue);//this->at(y, x) = identityValue;
            else
                localalloc.construct(this->datas + (x * Y + y), static_cast<T>(0));//this->at(y, x) = static_cast<T>(0);
        }
    }
}

MATRIX_TEMPLATE
Matrix<X, Y, T, ALLOC>::~Matrix() noexcept
{   this->Destroy();    }

    // METHODES

MATRIX_TEMPLATE
void Matrix<X, Y, T, ALLOC>::Destroy() noexcept
{
    localalloc.destroy(this->datas);
    localalloc.deallocate(this->datas, X * Y);
    this->datas = nullptr;
}

MATRIX_TEMPLATE
void Matrix<X, Y, T, ALLOC>::Free() noexcept
{
    this->~Matrix();
    delete (this);
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Scale(const Vector3<T>& vec3) noexcept
{
    this->at(0, 0)  =  vec3.x;
    this->at(1, 1)  =  vec3.y;
    this->at(2, 2)  =  vec3.z;
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Scale2D(const Vector2<T>& vec2) noexcept
{
    this->at(0, 0)  =  vec2.x;
    this->at(1, 1)  =  vec2.y;
}



MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Translation(const Vector3<T>& vec3) noexcept
{
    this->at(3, 0)  = vec3.x;
    this->at(3, 1)  = vec3.y;
    this->at(3, 2)  = vec3.z;
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Translation2D(const Vector2<T>& vec2) noexcept
{
    this->at(2, 0) = vec2.x;
    this->at(2, 1) = vec2.y;
}



MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Rotation(const Vector3<T>& _axis, const float& angle) noexcept
{
    const float c = cos(angle);
    const float s = sin(angle);
    const float t = 1.0f - c;
    Vector3<T> axis = _axis.Magnitude();

    const float tx = t * axis.x;
    const float ty = t * axis.y;
    const float tz = t * axis.z;

    const float sx = s * axis.x;
    const float sy = s * axis.y;
    const float sz = s * axis.z;

    const float txy = tx * axis.y;
    const float tyz = tx * axis.z;
    const float txz = ty * axis.z;

    Matrix4 originalMatrix(*this);

    this->at(0, 0) = originalMatrix.at(0, 0) * (tx * axis.x + c) + originalMatrix.at(1, 0) * (txy - sz) + originalMatrix.at(2, 0) * (txz + sy);
    this->at(1, 0) = originalMatrix.at(0, 0) * (txy + sz) + originalMatrix.at(1, 0) * (ty * axis.y + c) + originalMatrix.at(2, 0) * (tyz - sx);
    this->at(2, 0) = originalMatrix.at(0, 0) * (txz - sy) + originalMatrix.at(1, 0) * (tyz + sx) + originalMatrix.at(2, 0) * (tz * axis.z + c);

    this->at(0, 1) = originalMatrix.at(0, 1) * (tx * axis.x + c) + originalMatrix.at(1, 1) * (txy - sz) + originalMatrix.at(2, 1) * (txz + sy);
    this->at(1, 1) = originalMatrix.at(0, 1) * (txy + sz) + originalMatrix.at(1, 1) * (ty * axis.y + c) + originalMatrix.at(2, 1) * (tyz - sx);
    this->at(2, 1) = originalMatrix.at(0, 1) * (txz - sy) + originalMatrix.at(1, 1) * (tyz + sx) + originalMatrix.at(2, 1) * (tz * axis.z + c);

    this->at(0, 2) = originalMatrix.at(0, 2) * (tx * axis.x + c) + originalMatrix.at(1, 2) * (txy - sz) + originalMatrix.at(2, 2) * (txz + sy);
    this->at(1, 2) = originalMatrix.at(0, 2) * (txy + sz) + originalMatrix.at(1, 2) * (ty * axis.y + c) + originalMatrix.at(2, 2) * (tyz - sx);
    this->at(2, 2) = originalMatrix.at(0, 2) * (txz - sy) + originalMatrix.at(1, 2) * (tyz + sx) + originalMatrix.at(2, 2) * (tz * axis.z + c);

        // Appliquer le reste de la rotation
    float temp[16];
    temp[0] = originalMatrix.at(3, 0);
    temp[1] = originalMatrix.at(3, 1);
    temp[2] = originalMatrix.at(3, 2);

    this->at(3, 0) = -sx * temp[0] + c * temp[1];
    this->at(3, 1) = -sy * temp[0] + c * temp[1];
    this->at(3, 2) = -sz * temp[0] + c * temp[1];

    //for (uint8 i = 0; i < 3; ++i)
    //{
        //this->at(i, 3) = originalMatrix.at(i, 3);
        //this->at(3, i) = originalMatrix.at(3, i);
    //}
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Rotation2D(const Vector2<T>& vec2) noexcept
{
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Transformation( const Vector3<T>& pos,
                                                    const Vector3<T>& scale,
                                                    const Vector3<T>& rot)      noexcept
{
    this->Translation(pos);
    this->Scale      (scale);
    //this->Rotation   (rot);
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Transformation2D(   const Vector2<T>& pos,
                                                        const Vector2<T>& scale,
                                                        const Vector2<T>& rot)      noexcept
{
    this->Translation(pos);
    this->Scale      (scale);
    //this->Rotation   (rot);
}



MATRIX_TEMPLATE
void Matrix<X, Y, T, ALLOC>::LookAt (const Vector3<T>& eye,
                              const Vector3<T>& center,
                              const Vector3<T>& up)                         noexcept
{
    const Vector3<T> f(Vector3<T>::Magnitude(eye - center));
    const Vector3<T> s(Vector3<T>::Magnitude(Vector3<T>::Cross(f, up)));
    const Vector3<T> u(Vector3<T>::Cross(s, f));

         // X modification
    this->at(0, 0)  =  s.x;
    this->at(1, 0)  =  s.y;
    this->at(2, 0)  =  s.z;
        // Y modification
    this->at(0, 1)  =  u.x;
    this->at(1, 1)  =  u.y;
    this->at(2, 1)  =  u.z;
        // Z modification
    this->at(0, 2)  =  -f.x;
    this->at(1, 2)  =  -f.y;
    this->at(2, 2)  =  -f.z;
        // camera_position modification
    this->at(3, 0)  = -Vector3f::Dot(s, eye);
    this->at(3, 1)  = -Vector3f::Dot(u, eye);
    this->at(3, 2)  =  Vector3f::Dot(f, eye);
}

MATRIX_TEMPLATE
void Matrix<X, Y, T, ALLOC>::Perspective(const float& FOV, const float& width,
                                  const float& height, const float& zNear,
                                  const float& zFar)                            noexcept
{
    const float tanFOV   = tanf( static_cast<float>( Maths::deg_to_rad(FOV) / 2.0f ) );
    const float aspect   =       static_cast<float>( width / height   );

    this->at(0, 0) = static_cast<T>(1.0f / (aspect * tanFOV));
    this->at(1, 1) = static_cast<T>(1.0f / tanFOV);
    this->at(2, 2) = static_cast<T>(zFar / (zFar - zNear));
    this->at(3, 2) = static_cast<T>(-(zFar + zNear) / (zFar - zNear));
    this->at(2, 3) = static_cast<T>(1);
}



MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Debug() const
{
    if (this->datas == nullptr)
    {
        throw ("matrix datas = nullptr");
        return;
    }
    for (uint16 i = 0; i < (X * Y); i++)
    {
        if (i % 4 == 0)
            printf(" |  ");
        printf("%f ", *(&this->datas[0] + i));
    }
    printf("\n");
}

MATRIX_TEMPLATE
inline T* Matrix<X, Y, T, ALLOC>::Ref() const noexcept
{
    return (&this->datas[0]);
}