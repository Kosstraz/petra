#include "../Camera.hpp"

#include <rendering/RendererManager.hpp>

    /// CONSTRUCTEURS

#define FOV    (90.0F  )
#define ZNEAR  (0.01F  )
#define ZFAR   (100.0F )

Camera::Camera(const char* name) : PetraO(name), at(Vector3f(0.0f)), PROJ(new Matrix4(1.0f)), VIEW(new Matrix4(1.0f))
{
    this->transform.position = Vector3f(4.0f, 3.0f, 3.0f);
    this->transform.scale    = Vector3f(0.0f);
    this->transform.rotation = Vector3f(0.0f);

    this->PROJ->Perspective(FOV, (float)(Handle::window_size.x), (float)(Handle::window_size.y), ZNEAR, ZFAR);
    this->VIEW->LookAt( this->transform.position,
                        this->at,
                        Vector3f::UP());

        // Utilisation shader
    PushMatProgram(this->PROJ, "PROJECTION", (-1));
    PushMat(this->VIEW, "VIEW");
}

Camera::~Camera()
{
    this->Destroy();  // !'V1053 Calling the 'Destroy' virtual function in the destructor may lead to unexpected result at runtime. Camera.cpp 23'
}

    /// METHODES

void Camera::SetPosition(const Vector3f& position) noexcept
{
    this->transform.position = position;
    this->VIEW->LookAt( this->transform.position,
                        this->at,
                        Vector3f::UP());

        // Utilisation shader
    PushMatProgram(this->VIEW, "VIEW", (-1));
}

void Camera::Perspective() noexcept
{
    this->PROJ->Perspective(FOV, (float)(Handle::window_size.x), (float)(Handle::window_size.y), ZNEAR, ZFAR);

    PushMatProgram(this->PROJ, "PROJECTION", (-1));
}

void Camera::LookAt(const Vector3f& at) noexcept
{
    this->at = at;
    this->VIEW->LookAt( this->transform.position,
                        this->at,
                        Vector3f::UP());

        // Utilisation shader
    PushMatProgram(this->VIEW, "VIEW", (-1));
}

void Camera::Destroy() noexcept
{
    if (this->VIEW != nullptr)
    {
        delete (this->VIEW) ;
        this->VIEW = nullptr;
    }

    if (this->PROJ != nullptr)
    {
        delete (this->PROJ) ;
        this->PROJ = nullptr;
    }
}