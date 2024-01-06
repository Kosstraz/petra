#include "../Camera.hpp"

#include <rendering/RendererManager.hpp>

    /// CONSTRUCTEURS

Camera::Camera(const char* name) : PetraO(name), at(Vector3f(0.0f))
{
    this->transform.position = Vector3f(4.0f, 3.0f, 3.0f);

        // glm TEST
    this->PROJ = glm::perspective(glm::radians(60.f), (float)(800.f/600.f), 0.01f, 1000.0f);
    this->VIEW = glm::lookAt(     glm::vec3(this->transform.position.x, this->transform.position.y, this->transform.position.z),
                                  glm::vec3(0.0f, 0.0f, 0.0f),
                                  glm::vec3(0.0f, 1.0f, 0.0f));

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

        // glm TEST
    this->VIEW = glm::lookAt(   glm::vec3(this->transform.position.x, this->transform.position.y, this->transform.position.z),
                                glm::vec3(this->at.x,                 this->at.y,                 this->at.z),
                                glm::vec3(0.0f, 1.0f, 0.0f));

        // Utilisation shader
    PushMatProgram(this->VIEW, "VIEW", (-1));
}

void Camera::LookAt(Vector3f at) noexcept
{
    this->at = at;

        // glm TEST
    this->VIEW = glm::lookAt(   glm::vec3(this->transform.position.x, this->transform.position.y, this->transform.position.z),
                                glm::vec3(this->at.x,                   this->at.y,                     this->at.z),
                                glm::vec3(0.0f, 1.0f, 0.0f));

        // Utilisation shader
    PushMatProgram(this->VIEW, "VIEW", (-1));
}

void Camera::Destroy() noexcept
{

}