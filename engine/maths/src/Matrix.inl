#include "../Matrix.hpp"

    // CONSTRUCTEURS

MATRIX_TEMPLATE
Matrix<X, Y, T>::Matrix() : datas(new T[X * Y])
{
    for (uint8 x = 0; x < X; x++)
    {
        //this->datas[x] = new T[Y];
        for (uint8 y = 0; y < Y; y++)
            this->at(y, x) = static_cast<T>(0);//this->datas[x][y] = static_cast<T>(0);
    }
}

MATRIX_TEMPLATE
Matrix<X, Y, T>::Matrix(const T identityValue) : datas(new T[X * Y])
{
    for (uint8 x = 0; x < X; x++)
    {
        //this->datas[x]  =  new T[Y];
        for (uint8 y = 0; y < Y; y++)
        {
            if (x == y)
                this->at(y, x) = identityValue;//this->datas[x][y] = identityValue;
            else
                this->at(y, x) = static_cast<T>(0);//this->datas[x][y] = static_cast<T>(0);
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
    this->at(0, 0)  =  vec3.x;
    this->at(1, 1)  =  vec3.y;
    this->at(2, 2)  =  vec3.z;
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Scale2D(const Vector2<T>& vec2) noexcept
{
    this->at(0, 0)  =  vec2.x;
    this->at(1, 1)  =  vec2.y;
}



MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Translation(const Vector3<T>& vec3) noexcept
{
    this->at(0, 3)  = vec3.x;
    this->at(1, 3)  = vec3.y;
    this->at(2, 3)  = vec3.z;
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Translation2D(const Vector2<T>& vec2) noexcept
{
    this->at(0, 2) = vec2.x;
    this->at(1, 2) = vec2.y;
}



MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Rotation(const Vector3<T>& vec3) noexcept
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
inline void Matrix<X, Y, T>::Rotation2D(const Vector2<T>& vec2) noexcept
{
    /*this->datas[0] *= static_cast<T>( cosf(vec2.x));
    this->datas[1]  = static_cast<T>(-sinf(vec2.x));
    this->datas[4]  = static_cast<T>( sinf(vec2.x));
    this->datas[5] *= static_cast<T>( cosf(vec2.x));*/
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Transformation(const Vector3<T>& pos,
                                            const Vector3<T>& scale,
                                            const Vector3<T>& rot)      noexcept
{
    this->Translation(pos);
    this->Scale      (scale);
    //this->Rotation   (rot);
}

MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Transformation2D(const Vector2<T>& pos,
                                              const Vector2<T>& scale,
                                              const Vector2<T>& rot)      noexcept
{
    this->Translation(pos);
    this->Scale      (scale);
    //this->Rotation   (rot);
}



MATRIX_TEMPLATE
void Matrix<X, Y, T>::LookAt (const Vector3<T>& eye,
                              const Vector3<T>& center,
                              const Vector3<T>& up)                         noexcept
{
    const Vector3f f(Vector3f::Magnitude(eye - center));
    const Vector3f s(Vector3f::Magnitude(Vector3f::Cross(f, up)));
    const Vector3f u(Vector3f::Cross(s, f));

         // X modification
    this->at(0, 0)  =  f.x;
    this->at(0, 1)  =  f.y;
    this->at(0, 2)  =  f.z;
        // Y modification
    this->at(1, 0)  =  s.x;
    this->at(1, 1)  =  s.y;
    this->at(1, 2)  =  s.z;
        // Z modification
    this->at(2, 0)  =  u.x;
    this->at(2, 1)  =  u.y;
    this->at(2, 2)  =  u.z;
        // camera_position modification
    this->at(0, 3)  = -Vector3f::Dot(s, eye);
    this->at(1, 3)  = -Vector3f::Dot(u, eye);
    this->at(2, 3)  = -Vector3f::Dot(f, eye);
}

MATRIX_TEMPLATE
void Matrix<X, Y, T>::Perspective(const float& FOV, const float& width,
                                  const float& height, const float& zNear,
                                  const float& zFar)                            noexcept
{
    const float tanFOV   = tanf( static_cast<float>( Maths::deg_to_rad(FOV) / 2.0f ) );
    const float aspect   =       static_cast<float>( width / height   );

    this->at(0, 0) = static_cast<T>(1.0f / (aspect * tanFOV));
    this->at(1, 1) = static_cast<T>(1.0f / tanFOV);
    this->at(2, 2) = static_cast<T>(zFar / (zFar - zNear));
    this->at(2, 3) = static_cast<T>((-zFar * zNear) / (zFar - zNear)); 
    this->at(3, 2) = static_cast<T>(1);
}



MATRIX_TEMPLATE
inline void Matrix<X, Y, T>::Debug() const
{
    if (this->datas == nullptr)
    {
        throw ("matrix datas = nullptr");
        return;
    }
    for (uint16 i = 0; i < (X * Y); i++)
        printf("%f", this->datas[i]);
}

MATRIX_TEMPLATE
inline T* Matrix<X, Y, T>::Ref() const noexcept
{
    return (&this->datas[0]);
}