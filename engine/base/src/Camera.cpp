#include "../Camera.hpp"

#include <rendering/RendererManager.hpp>

    /// CONSTRUCTEURS

Camera::Camera(const char* name) : PetraO(name), at(Vector3f(0.0f)), PROJ(new Matrix4(1.0f)), VIEW(new Matrix4(1.0f))
{
    this->transform.position = Vector3f(4.0f, 3.0f, 3.0f);

    this->PROJ->Perspective(90.f, (float)(Handle::window_size.x), (float)(Handle::window_size.y), 0.1f, 1000.0f);
    this->VIEW->LookAt( this->transform.position,
                        this->at,
                        Vector3f(0.f, 1.0f, 0.0f));

        // Utilisation shader
    PushMatProgram(this->PROJ, "PROJECTION", (-1));
    PushMat(this->VIEW, "VIEW");
}

Camera::~Camera()
{
    this->Destroy();
}

    /// METHODES

void Camera::SetPosition(Vector3f position) noexcept
{
    this->transform.position = position;
    this->VIEW->LookAt( this->transform.position,
                        this->at,
                        Vector3f(0.f, 1.0f, 0.0f));

        // Utilisation shader
    PushMatProgram(this->VIEW, "VIEW", (-1));
}

void Camera::Perspective(int window_width, int window_height) noexcept
{
    this->PROJ->Perspective(90.f, (float)(Handle::window_size.x), (float)(Handle::window_size.y), 0.1f, 1000.0f);

    PushMatProgram(this->PROJ, "PROJECTION", (-1));
}

void Camera::LookAt(Vector3f at) noexcept
{
    this->at = at;

    this->VIEW->LookAt( this->transform.position,
                        this->at,
                        Vector3f(0.f, 1.0f, 0.0f));

        // Utilisation shader
    PushMatProgram(this->VIEW, "VIEW", (-1));
}

void Camera::Destroy() noexcept
{
    delete (this->VIEW);
    delete (this->PROJ);
}