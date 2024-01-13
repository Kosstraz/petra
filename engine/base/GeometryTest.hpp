#ifndef PETRA_GEOMETRYTEST_HPP
#define PETRA_GEOMETRYTEST_HPP

#include <glad/glad.h>
#define GLFW_DLL
#include <glfw-3.3.9/glfw3.h>

#include <rendering/Texture.hpp>

#include <base/PetraO.hpp>
#include <C/Transform.h>
#include <maths/Matrix.hpp>
#include <rendering/Shader.hpp>
#include <core/Handle.hpp>

#define DRAW_TRIANGLE   0x00
#define DRAW_SQUARE     0x01
#define DRAW_CUBE       0x02

class GeometryTest final : public PetraO
{
public:
        /// CONSTRUCTEURS

    GeometryTest(const char* name);
    ~GeometryTest() noexcept override;

        /// METHODES

    void WhatBuild     (uint8 DRAW_WHAT)                                        ;
    void BuildTriangle (uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)         noexcept;
    void BuildSquare   (uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)         noexcept;
    void BuildCube     (uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)         noexcept;

    virtual void Build(uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)          noexcept override;
    virtual void DrawBuild()                                   const    noexcept override   FREQ;
    void PutTexture(uint32 textureID) noexcept;

    void SetPosition(const Vector3f& position)  noexcept    FREQ;
    void SetScale   (const Vector3f& scale   )  noexcept;
    void SetRotation(const Vector3f& rotation)  noexcept;

    void SetColor   (const Vector3f color)      noexcept;

    virtual void Destroy() noexcept override;
    inline const bool operator==(const GeometryTest& b) const noexcept
    {
        if (strcmp(this->name, b.name) == 0)
            return (true);
        return (false);
    }

    READ_ONLY Transform   transform;
    READ_ONLY Vector3f    color;
private:
    uint8   what_build;
    uint    GL_GEOMETRY;
    uint    uvsBufferID;
    uint    vertexArrayID;
    uint    vertexBufferID;
    uchar   verticesToDraw;

    Matrix4*  MOD;
};

#endif