#ifndef PETRA_CUBE_HPP
#define PETRA_CUBE_HPP

#include <base/GeometryTest.hpp>

class Cube final : public GeometryTest
{
public:

    Cube(const char* name);
   ~Cube();

    virtual void Build(uint32 GL_METHOD_DRAW = GL_STATIC_DRAW)    noexcept    override;
    virtual void DrawBuild()                             const    noexcept    override   FREQ;

        // 0 Front
        // 1 Back
        // 2 Right
        // 3 Left
        // 4 Top
        // 5 Bot
    void PutMultiplesTextures(const char* textureNames[6])        noexcept;

    virtual void Destroy() noexcept override;

private:
    void FrontFace()    noexcept;
    void BackFace ()    noexcept;
    void RightFace()    noexcept;
    void LeftFace ()    noexcept;
    void TopFace  ()    noexcept;
    void BotFace  ()    noexcept;

    uint8   faceCount;
    uint*   vertexBuffersID;
    uint*   uvsBuffersID;
    uint*   textureBuffersID;
};

#endif