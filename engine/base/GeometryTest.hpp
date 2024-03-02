#ifndef PETRA_GEOMETRYTEST_HPP
#define PETRA_GEOMETRYTEST_HPP

#include <glad/glad.h>
#define GLFW_DLL
#include <glfw-3.3.9/glfw3.h>

#include <rendering/Texture.hpp>

#include <base/PetraO.hpp>
#include <maths/Transform.hpp>
#include <maths/Matrix.hpp>
#include <rendering/Shader.hpp>
#include <core/Handle.hpp>

#include <rendering/RendererManager.hpp>

#define DRAW_TRIANGLE   (0x00)
#define DRAW_SQUARE     (0x01)
#define DRAW_CUBE       (0x02)

class GeometryTest : public PetraO
{
public:
        /// CONSTRUCTEURS

    GeometryTest(const char* name);
    ~GeometryTest() noexcept override;

        /// METHODES

    virtual void WhatBuild(uint8 DRAW_WHAT);

    void BuildTriangle     (uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)         noexcept;
    void BuildSquare       (uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)         noexcept;
    void BuildCube         (uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)         noexcept;

    virtual void Build(uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)          noexcept override;
    virtual void DrawBuild()                                   const    noexcept override   FREQ;
    virtual void PutTexture(const char* textureName)                    noexcept;

    virtual void SetPosition(const Vector3f& position)  noexcept    FREQ;
    virtual void SetScale   (const Vector3f& scale   )  noexcept;
    virtual void SetRotation(const Vector3f& rotation, const float& angle)  noexcept;

    virtual void SetColor   (const Color3& color)       noexcept;

    virtual void Destroy() noexcept override;
    inline const BOOL operator==(const GeometryTest& b) const noexcept
    {
        if (strcmp(this->name, b.name) == 0x00)
            return (0x01);                      // true
        return (0x00);                          // false
    }
    
    READ_ONLY Transform   transform;
    READ_ONLY Color3      color;

protected:
    uint        vertexArrayID;
    Matrix4*    SP;

private:
    uchar   verticesToDraw;
    uint    GL_GEOMETRY;
    uint8   what_build;
    uint    uvsBufferID;
    uint    vertexBufferID;
};

#endif