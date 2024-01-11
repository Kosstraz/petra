#include "../Camera.hpp"

#include <rendering/RendererManager.hpp>

    /// CONSTRUCTEURS

Camera::Camera(const char* name) : PetraO(name), at(Vector3f(0.0f))
{
    this->transform.position = Vector3f(4.0f, 3.0f, 3.0f);

        // glm TEST
    this->PROJ = glm::perspective(glm::radians(90.f), (float)(Handle::window_size.x / Handle::window_size.y), 0.1f, 100.0f);
    this->VIEW = glm::lookAt(     glm::vec3(this->transform.position.x, this->transform.position.y, this->transform.position.z),
                                  glm::vec3(this->at.x,                 this->at.y,                 this->at.z),
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

void Camera::Perspective(int window_width, int window_height) noexcept
{
    //int w, h;
    //glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
    this->PROJ = glm::perspective(glm::radians(70.f), (float)(window_width / window_height), 0.1f, 100.0f);

    PushMatProgram(this->PROJ, "PROJECTION", (-1));
}

void Camera::LookAt(Vector3f at) noexcept
{
    this->at = at;

        // glm TEST
    this->VIEW = glm::lookAt(   glm::vec3(this->transform.position.x, this->transform.position.y, this->transform.position.z),
                                glm::vec3(at.x,                       at.y,                       at.z),
                                glm::vec3(0.0f, 1.0f, 0.0f));

        // Utilisation shader
    //PushMat(this->VIEW, "VIEW");
    PushMatProgram(this->VIEW, "VIEW", (-1));
}

void Camera::Destroy() noexcept
{

}