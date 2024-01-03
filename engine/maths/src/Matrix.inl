#include "../Matrix.hpp"

    // CONSTRUCTEURS

MATRIX_TEMPLATE
Matrix<X, Y, T>::Matrix()
{
    this->datas = new T[X * Y];

    for (uint32 i = 0; i < (X * Y); i++)
        this->datas[i] = static_cast<T>(0);
}

MATRIX_TEMPLATE
Matrix<X, Y, T>::Matrix(const T identityValue)
{
    this->datas = new T[X * Y];

    for (uint16 i = 0; i < Y; i++)
    {
        for (uint16 j = 0; j < X; j++)
        {
            if (i - j == 0)
                this->datas[(Y * i) + j] = identityValue;
            else
                this->datas[(Y * i) + j] = static_cast<T>(0);
        }
    }
}

MATRIX_TEMPLATE
Matrix<X, Y, T>::~Matrix() noexcept
{
   this->Free();
}

    // METHODES

MATRIX_TEMPLATE
void Matrix<X, Y, T>::Free() noexcept
{
    delete[] this->datas;
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Scale(const Vector3<T>& vec3) noexcept
{
    this->datas[0] = vec3.x;    
    this->datas[5] = vec3.y;
    this->datas[10] = vec3.z;
    this->datas[15] = static_cast<T>(1);
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Scale(const Vector2<T>& vec2) noexcept
{
    this->datas[0] = vec2.x;
    this->datas[4] = vec2.y;
    this->datas[8] = static_cast<T>(1);
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Scale(const T value) noexcept
{   
    this->datas[0] = value;
    if (Y == 4 && X == 4)
    {
        this->datas[5] = value;
        this->datas[10] = value;
        this->datas[15] = static_cast<T>(1);
    }
    else if (Y == 3 && X == 3)
    {
        this->datas[4] = value;
        this->datas[8] = static_cast<T>(1);
    }
}



MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Translation(const Vector3<T>& vec3) noexcept
{
    this->datas[0]  = vec3.x;
    this->datas[5]  = vec3.y;
    this->datas[10] = vec3.z;
    this->datas[15] = static_cast<T>(1);
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Translation(const Vector2<T>& vec2) noexcept
{
    this->datas[0] = vec2.x;
    this->datas[4] = vec2.y;
    this->datas[8] = static_cast<T>(1);
}



MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Rotation(const Vector3<T>& vec3) noexcept
{
            // X-Rotation
        this->datas[5]  *= static_cast<T>( cosf(vec3.x));
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
        this->datas[5] *= static_cast<T>( cosf(vec3.z));
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Rotation(const T angle) noexcept
{
    this->datas[0] *= static_cast<T>( cosf(angle));
    this->datas[1]  = static_cast<T>(-sinf(angle));
    this->datas[4]  = static_cast<T>( sinf(angle));
    this->datas[5] *= static_cast<T>( cosf(angle));
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Transformation(const Vector3<T>& pos,
                                            const Vector3<T>& scale,
                                            const Vector3<T>& rot)      noexcept
{
    this->Translation(pos);
    this->Scale      (scale);
    this->Rotation   (rot);
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Transformation2D(const Vector2<T>& pos,
                                              const Vector2<T>& scale,
                                              const Vector2<T>& rot)      noexcept
{
    this->Translation(pos);
    this->Scale      (scale);
    this->Rotation   (rot);
}



MATRIX_TEMPLATE
void Matrix<X, Y, T>::LookAt (const Vector3<T>& eye,
                              const Vector3<T>& center,
                              const Vector3<T>& up)                  noexcept
{
    const Vector3f f(Vector3f::Magnitude(center - eye));
    const Vector3f s(Vector3f::Magnitude(Vector3f::Scalar(f, up, 90.f)));
    const Vector3f u(Vector3f::Scalar(s, f, 90.f));

         // X modification
    this->datas[0]  =  f.x;
    this->datas[1]  =  f.y;
    this->datas[2]  =  f.z;
        // Y modification
    this->datas[4]  =  s.x;
    this->datas[5]  =  s.y;
    this->datas[6]  =  s.z;
        // Z modification
    this->datas[8]  =  u.x;
    this->datas[9]  =  u.y;
    this->datas[10] =  u.z;
        // camera_position modification
    this->datas[3]  = -Vector3f::Dot(s, eye);
    this->datas[7]  = -Vector3f::Dot(u, eye);
    this->datas[11] = Vector3f::Dot(f, eye);
}

MATRIX_TEMPLATE
void Matrix<X, Y, T>::Perspective(const float& FOV, const float& width, 
                                  const float& height, const float& zNear, 
                                  const float& zFar)                         noexcept
{
    const T tanFOV   = static_cast<T>(tanf(Maths::deg_to_rad(FOV) / 2.0f));
    const T aspect   = static_cast<T>((float)width / (float)height);

    this->datas[0]  = static_cast<T>(1.0f / (aspect * tanFOV));
    this->datas[5]  = static_cast<T>(1.0f / tanFOV);
    this->datas[10] = static_cast<T>(zFar / (zFar - zNear));
    this->datas[11] = static_cast<T>(-(zFar * zNear) / (zFar - zNear));
    this->datas[14] = static_cast<T>(1);
}



MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Debug() const
{
    if (this->datas == nullptr)
    {
        throw ("matrix datas = nullptr");
        return;
    }
    for (unsigned short i = 0; i < (X * Y); i++)
        printf("%f\t", this->datas[i]);
    printf("\n");
}

MATRIX_TEMPLATE
inline T* Matrix<X, Y, T>::Ref() const noexcept
{
    return &(this->datas[0]);
}