#ifndef PETRA_CAMERA_HPP
#define PETRA_CAMERA_HPP

#include <glad/glad.h>

#include <base/PetraO.hpp>
#include <core/Handle.hpp>
#include <maths/Matrix.hpp>
#include <C/Transform.h>

class Camera final : public PetraO
{
public:
        /// CONSTRUCTEURS

    Camera(const char* name);
    ~Camera();

        /// METHODES

    void SetPosition(Vector3f position) noexcept;
    void SetScale   (Vector3f scale)    noexcept;
    void SetRotation(Vector3f rotation) noexcept;

    // read only
    READ_ONLY Transform transform;

private:
    Matrix4x4f* projection;
    Matrix4x4f* view;
};

#endif