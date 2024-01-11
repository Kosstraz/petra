#ifndef PETRA_CAMERA_HPP
#define PETRA_CAMERA_HPP

#include <glad/glad.h>
#define GLFW_DLL
#include <glfw-3.3.9/glfw3.h>

#include <base/PetraO.hpp>
#include <core/Handle.hpp>
#include <maths/Matrix.hpp>
#include <C/Transform.h>

class Camera : public PetraO
{
public:
        /// CONSTRUCTEURS

    Camera(const char* name);
    ~Camera() override;

        /// METHODES

    void SetPosition(Vector3f position) noexcept;
    void Perspective(int window_width, int window_height) noexcept;
    void LookAt     (Vector3f at)       noexcept;

    virtual void Destroy() noexcept override;

    // read only
    READ_ONLY Transform transform;
    READ_ONLY Vector3f  at       ;

private:
        // glm TEST
    glm::mat4  VIEW;
    glm::mat4  PROJ;
};

#endif