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
inline void Matrix<X, Y, T, ALLOC>::Rotation(const Vector3<T>& vec3) noexcept
{
            // X-Rotation
        /*this->datas[5]  *= static_cast<T>( cosf(vec3.x));
        this->datas[6]   = static_cast<T>(-sinf(vec3.x));
        this->datas[9]   = static_cast<T>( sinf(vec3.x));
        this->datas[10] *= static_cast<T>( cosf(vec3.x));   

            // Y-Rotation
        this->datas[0]  *= static_cast<T>( cosf(vec3.y));
        this->datas[2]   = static_cast<T>( sinf(vec3.y));
        this->datas[8]   = static_cast<T>(-sinf(vec3.y));
        this->datas[10] *= static_cast<T>( cosf(vec3.y));
        
            // Z-Rotation
        this->datas[0] *= static_cast<T>( cosf(vec3.z));
        this->datas[1]  = static_cast<T>(-sinf(vec3.z));
        this->datas[4]  = static_cast<T>( sinf(vec3.z));
        this->datas[5] *= static_cast<T>( cosf(vec3.z));*/
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Rotation2D(const Vector2<T>& vec2) noexcept
{
    /*this->datas[0] *= static_cast<T>( cosf(vec2.x));
    this->datas[1]  = static_cast<T>(-sinf(vec2.x));
    this->datas[4]  = static_cast<T>( sinf(vec2.x));
    this->datas[5] *= static_cast<T>( cosf(vec2.x));*/
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Transformation(const Vector3<T>& pos,
                                            const Vector3<T>& scale,
                                            const Vector3<T>& rot)      noexcept
{
    this->Translation(pos);
    this->Scale      (scale);
    //this->Rotation   (rot);
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T, ALLOC>::Transformation2D(const Vector2<T>& pos,
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
    const Vector3f f(Vector3f::Magnitude(eye - center));
    const Vector3f s(Vector3f::Magnitude(Vector3f::Cross(f, up)));
    const Vector3f u(Vector3f::Cross(s, f));

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
    this->at(3, 2) = static_cast<T>((-zFar * zNear) / (zFar - zNear)); 
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