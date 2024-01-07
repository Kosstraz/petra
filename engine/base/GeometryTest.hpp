#ifndef PETRA_GEOMETRYTEST_HPP
#define PETRA_GEOMETRYTEST_HPP

#include <glad/glad.h>
#define GLFW_DLL
#include <glfw-3.3.9/glfw3.h>

#include <base/PetraO.hpp>
#include <C/Transform.h>
#include <maths/Matrix.hpp>
#include <rendering/Shader.hpp>
#include <core/Handle.hpp>

#define DRAW_TRIANGLE   0
#define DRAW_SQUARE     1
#define DRAW_CUBE       2

class GeometryTest final : public PetraO
{
public:
        /// CONSTRUCTEURS

    GeometryTest(const char* name);
    ~GeometryTest() noexcept override;

        /// METHODES

    void WhatBuild     (uint8 DRAW_WHAT)                                  ;
    void BuildTriangle (uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)   noexcept;
    void BuildSquare   (uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)   noexcept;
    void BuildCube     (uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)   noexcept;

    virtual void Build(uint32 GL_METHOD_DRAW = GL_STATIC_DRAW) noexcept override;
    virtual void DrawBuild()                                   noexcept override;

    void SetPosition(const Vector3f& position) noexcept;
    void SetScale   (const Vector3f& scale   ) noexcept;
    void SetRotation(const Vector3f& rotation) noexcept;

    void SetColor(const Vector3f color) noexcept;

    virtual void Destroy() noexcept override;

    READ_ONLY Transform   transform;
    READ_ONLY Vector3f    color;
private:
    uint8   what_build;
    uint    GL_GEOMETRY;
    uint    vertexArrayID;
    uint    vertexBufferID;
    uchar   verticesToDraw;

    glm::mat4   MOD;
};

#endif